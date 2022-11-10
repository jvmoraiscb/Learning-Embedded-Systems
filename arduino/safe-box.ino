/*
  Debounce

  Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached from pin 2 to +5V
  - 10 kilohm resistor attached from pin 2 to ground

  - Note: On most Arduino boards, there is already an LED on the board connected
    to pin 13, so you don't need any extra components for this example.

  created 21 Nov 2006
  by David A. Mellis
  modified 30 Aug 2011
  by Limor Fried
  modified 28 Dec 2012
  by Mike Walters
  modified 30 Aug 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
*/

// buttons pins:
const int buzzerPin = 10;
const int greenLedPin = 9;
const int redLedPin = 8;
const int buttonPin_1 = 7;
const int buttonPin_2 = 6;
const int buttonPin_3 = 5;
const int buttonPin_4 = 4;
const int buttonPin_5 = 3;
const int buttonPin_R = 2;

/********************* buttons properties *********************/
int buttonState_1;            // the current reading from the input pin
int lastButtonState_1 = HIGH; // the previous reading from the input pin
bool buttonDown_1 = false;
bool buttonUp_1 = false;
unsigned long lastDebounceTime_1 = 0; // the last time the output pin was toggled

int buttonState_2;            // the current reading from the input pin
int lastButtonState_2 = HIGH; // the previous reading from the input pin
bool buttonDown_2 = false;
bool buttonUp_2 = false;
unsigned long lastDebounceTime_2 = 0; // the last time the output pin was toggled

int buttonState_3;            // the current reading from the input pin
int lastButtonState_3 = HIGH; // the previous reading from the input pin
bool buttonDown_3 = false;
bool buttonUp_3 = false;
unsigned long lastDebounceTime_3 = 0; // the last time the output pin was toggled

int buttonState_4;            // the current reading from the input pin
int lastButtonState_4 = HIGH; // the previous reading from the input pin
bool buttonDown_4 = false;
bool buttonUp_4 = false;
unsigned long lastDebounceTime_4 = 0; // the last time the output pin was toggled

int buttonState_5;            // the current reading from the input pin
int lastButtonState_5 = HIGH; // the previous reading from the input pin
bool buttonDown_5 = false;
bool buttonUp_5 = false;
unsigned long lastDebounceTime_5 = 0; // the last time the output pin was toggled

int buttonState_R;            // the current reading from the input pin
int lastButtonState_R = HIGH; // the previous reading from the input pin
bool buttonDown_R = false;
bool buttonUp_R = false;
unsigned long lastDebounceTime_R = 0; // the last time the output pin was toggled

unsigned long debounceDelay = 50; // the debounce time
/********************* buttons properties *********************/

const int passwordSize = 5;
int password[passwordSize] = {1, 2, 3, 4, 5};

int passwordAt[passwordSize];
int pass_i = 0;

int attempts = 0;

bool isLocked = true;
bool isChangingPassword = false;

void setup()
{
    Serial.begin(9600);

    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    pinMode(buttonPin_1, INPUT_PULLUP);
    pinMode(buttonPin_2, INPUT_PULLUP);
    pinMode(buttonPin_3, INPUT_PULLUP);
    pinMode(buttonPin_4, INPUT_PULLUP);
    pinMode(buttonPin_5, INPUT_PULLUP);
    pinMode(buttonPin_R, INPUT_PULLUP);

    digitalWrite(buzzerPin, LOW);
}

void loop()
{
    if (isLocked)
    {
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
    }
    else
    {
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
    }

    int digit = allButtonsDebounce();

    if (digit != 0)
    {
        if (isLocked)
        {
            if (digit == -1)
            {
                Serial.println("\nreset attempt!");
                pass_i = 0;
                beepSound();
            }
            else if (pass_i < passwordSize)
            {
                Serial.print(digit);
                passwordAt[pass_i] = digit;
                pass_i++;
                beepSound();
            }

            if (pass_i == passwordSize)
            {
                Serial.println();
                bool isEqual = comparePasswords(password, passwordAt);
                if (isEqual)
                {
                    isLocked = false;
                    Serial.println("safe-box unlocked!");
                    beepSound();
                    beepSound();
                }
                else
                {
                    Serial.print("wrong password");
                    attempts++;
                    digitalWrite(buzzerPin, HIGH);
                    if (attempts < 3)
                    {
                        Serial.println("!");
                        delay(500);
                    }
                    else
                    {
                        Serial.println(" three times in a row!");
                        delay(1500);
                        attempts = 0;
                    }
                    digitalWrite(buzzerPin, LOW);
                }
                pass_i = 0;
            }
        }
        else
        {
            if (!isChangingPassword)
            {
                if (digit == -1)
                {
                    Serial.print("insert the new password: ");
                    isChangingPassword = true;
                    beepSound();
                }
                else
                {
                    Serial.println("safe-box locked!");
                    isLocked = true;
                    beepSound();
                    beepSound();
                }
            }
            else
            {
                if (digit == -1)
                {
                    Serial.println("\npassword change canceled!");
                    isChangingPassword = false;
                    pass_i = 0;
                    beepSound();
                }
                else if (pass_i < passwordSize)
                {
                    Serial.print(digit);
                    passwordAt[pass_i] = digit;
                    pass_i++;
                    beepSound();
                }

                if (pass_i == passwordSize)
                {
                    Serial.println();
                    copyPasswords(password, passwordAt);
                    Serial.println("password change successfully!");
                    pass_i = 0;
                    isLocked = true;
                    beepSound();
                    beepSound();
                }
            }
        }
    }
}

int allButtonsDebounce()
{
    buttonDebounce(buttonPin_1, &lastButtonState_1, &lastDebounceTime_1, &buttonState_1, &buttonUp_1, &buttonDown_1);
    buttonDebounce(buttonPin_2, &lastButtonState_2, &lastDebounceTime_2, &buttonState_2, &buttonUp_2, &buttonDown_2);
    buttonDebounce(buttonPin_3, &lastButtonState_3, &lastDebounceTime_3, &buttonState_3, &buttonUp_3, &buttonDown_3);
    buttonDebounce(buttonPin_4, &lastButtonState_4, &lastDebounceTime_4, &buttonState_4, &buttonUp_4, &buttonDown_4);
    buttonDebounce(buttonPin_5, &lastButtonState_5, &lastDebounceTime_5, &buttonState_5, &buttonUp_5, &buttonDown_5);
    buttonDebounce(buttonPin_R, &lastButtonState_R, &lastDebounceTime_R, &buttonState_R, &buttonUp_R, &buttonDown_R);

    if (buttonDown_1 && buttonUp_1)
    {
        buttonDown_1 = false;
        buttonUp_1 = false;
        return 1;
    }
    if (buttonDown_2 && buttonUp_2)
    {
        buttonDown_2 = false;
        buttonUp_2 = false;
        return 2;
    }
    if (buttonDown_3 && buttonUp_3)
    {
        buttonDown_3 = false;
        buttonUp_3 = false;
        return 3;
    }
    if (buttonDown_4 && buttonUp_4)
    {
        buttonDown_4 = false;
        buttonUp_4 = false;
        return 4;
    }
    if (buttonDown_5 && buttonUp_5)
    {
        buttonDown_5 = false;
        buttonUp_5 = false;
        return 5;
    }
    if (buttonDown_R && buttonUp_R)
    {
        buttonDown_R = false;
        buttonUp_R = false;
        return -1;
    }
    return 0;
}

void buttonDebounce(int buttonPin, int *lastButtonState, unsigned long *lastDebounceTime, int *buttonState, bool *buttonUp, bool *buttonDown)
{
    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonPin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != *lastButtonState)
    {
        // reset the debouncing timer
        *lastDebounceTime = millis();
    }

    if ((millis() - *lastDebounceTime) > debounceDelay)
    {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != *buttonState)
        {
            *buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if (*buttonState == HIGH)
            {
                // ledState = !ledState;
                *buttonUp = true;
            }
            if (*buttonState == LOW)
            {
                *buttonDown = true;
            }
        }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    *lastButtonState = reading;
}

void beepSound()
{
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
}

bool comparePasswords(int *pass1, int *pass2)
{
    for (int i = 0; i < passwordSize; i++)
    {
        if (pass1[i] != pass2[i])
            return false;
    }
    return true;
}

void copyPasswords(int *pass1, int *pass2)
{
    for (int i = 0; i < passwordSize; i++)
    {
        pass1[i] = pass2[i];
    }
}
