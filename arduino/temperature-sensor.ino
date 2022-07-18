#define LED_VERMELHO 3
#define LED_AZUL 4
#define LED_VERDE 5
#define VALOR_AZUL 123
#define VALOR_VERDE 145
#define VALOR_AMARELO 164

void setup(){
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
}

void setRGB(byte red, byte green, byte blue){
  	digitalWrite(LED_VERMELHO, red);    	
  	digitalWrite(LED_VERDE, green);
  	digitalWrite(LED_AZUL, blue);
      	
}

void loop(){
	int sensorValue = analogRead(A0);
  	Serial.println(sensorValue);
  	if(sensorValue <= VALOR_AZUL){
    //<= 10 CELSIUS	
      	setRGB(LOW,LOW,HIGH);
      	//AZUL
    }
  	else if(sensorValue <= VALOR_VERDE){
    //<= 20 CELSIUS  	
      	setRGB(LOW, HIGH, LOW);
  		//VERDE
  	}
  	else if(sensorValue <= VALOR_AMARELO){
    //<= 30 CELSIUS)
      	setRGB(HIGH, HIGH, LOW);
      	//AMARELO
  	}
  	else{
      	setRGB(HIGH, LOW, LOW);
      	//VERMELHO
  	}
}