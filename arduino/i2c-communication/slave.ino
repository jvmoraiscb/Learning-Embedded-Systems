/** Master baseado no exemplo do
Arduino**/
#include <Wire.h>

const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;

byte modo = 0;

void setup() {

  	pinMode(2, INPUT_PULLUP);
  	attachInterrupt(0, pressionaBotao, FALLING);
  
	Wire.begin();
}

void loop() {
	Wire.beginTransmission(I2C_SLAVE);
	// transmit to device #8
  
 	Wire.write(modo);
  	Wire.endTransmission();
}

void pressionaBotao(){
	if(modo < 4)
  		modo++;
  	else
      	modo = 0;
}