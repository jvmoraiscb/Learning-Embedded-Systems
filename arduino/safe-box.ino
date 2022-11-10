// arduino ports
const int buzzer = 13;
const int button1 = 12;
const int button2 = 11;
const int button3 = 10;
const int button4 = 9;
const int button5 = 8;
const int buttonReset = 7;
const int ledRed = 6;
const int ledGreen = 5;

// code consts
const int passwordSize = 5;
const long debounceDelay = 50;

// safe box properties
bool isLocked = true;
bool isChangingPassword = false;
int password[passwordSize] = {1, 2, 3, 4, 5};

// password attempts properties
int triedPassword[passwordSize] = {0, 0, 0, 0, 0};
int pass_i = 0;
int digit = 0;
int attempts = 0;

// debounce property
long lastDebounceTime = 0;

void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);

    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(button4, INPUT);
    pinMode(button5, INPUT);
    pinMode(buttonReset, INPUT);
}

void loop()
{
    if (isLocked) // safe box locked
    {
        digitalWrite(ledRed, HIGH);
        digitalWrite(ledGreen, LOW);

        if (debounceButton(button1) || debounceButton(button2) || debounceButton(button3) || debounceButton(button4) || debounceButton(button5) || debounceButton(buttonReset))
        {
            if (digit == -1) // resets current password attempt
            {
                pass_i = 0;
            }
            else if (pass_i < passwordSize) // current password attempt
            {
                triedPassword[pass_i] = digit;
                pass_i++;
            }
            else // ends current password attempt
            {
                pass_i = 0; // reset pass_i to other attempt
                if (comparePasswords(password, triedPassword))
                {
                    isLocked = false;
                    attempts = 0;
                }
                else
                {
                    digitalWrite(buzzer, HIGH);
                    if (attempts < 3)
                        delay(500);
                    else
                    {
                        attempts = 0;
                        delay(1500);
                    }
                    digitalWrite(buzzer, LOW);
                }
            }
        }
        else // safe box unlocked
        {
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, HIGH);

            if (debounceButton(button1) || debounceButton(button2) || debounceButton(button3) || debounceButton(button4) || debounceButton(button5) || debounceButton(buttonReset))
            {
                if (digit == -1 && !isChangingPassword) // change password
                {
                    isChangingPassword = true;
                }
                else if (pass_i < passwordSize && isChangingPassword) // current password change
                {
                    password[pass_i] = digit;
                    pass_i++;
                }
                else // ends current password change
                {
                    isLocked = true;
                    isChangingPassword = false;
                    pass_i = 0;
                }
            }
        }
    }
}

bool comparePasswords(int pass1[], int pass2[])
{
    for (int i = 0; i < passwordSize; i++)
    {
        if (pass1[i] != pass2[i])
            return false;
    }
    return true;
}

bool debounceButton(int button)
{
    int buttonState = digitalRead(button);
    if (buttonState == HIGH)
    {
        if ((millis() - lastDebounceTime) > debounceDelay)
        {
            lastDebounceTime = millis();
            digit = buttonToDigit(button);
            return true;
        }
        return false;
    }
    lastDebounceTime = millis();
    return false;
}

int buttonToDigit(int button)
{
    switch (button)
    {
    case button1:
        return 1;
    case button2:
        return 2;
    case button3:
        return 3;
    case button4:
        return 4;
    case button5:
        return 5;
    case buttonReset:
    default:
        return -1;
    }
}
