// AUTORES: JOAO VICTOR MORAIS(MONTAGEM), TALLES CAVALLEIRO(MONTAGEM) E VINICIUS COLE(CODIGO)
// DISCIPLINA: PROJETO INTEGRADO DE COMPUTACAO (PIC)
#define CIMA 12000
#define BAIXO -12000
#define ESQUERDA 12000
#define DIREITA -12000

#include<Wire.h>
const int MPU=0x68;
int16_t AcX,AcY;

int retornaPosicao();
void imprimeCaractere(int cm1, int cm2, int cm3);

void setup(){
Wire.begin();
Wire.beginTransmission(MPU);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
}

void PiscaLed(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
}

int c1, c2, c3;
int c0;

void loop(){
digitalWrite(LED_BUILTIN, HIGH); // avisa que o codigo voltou para o inicio
delay(800);
digitalWrite(LED_BUILTIN, LOW);
delay(800);
do{
  c1 = retornaPosicao();  // espera ate que realize a primeira posicao
}while(c1 == 0);
PiscaLed();
delay(800);
do{
  c0 = retornaPosicao();  // espera ate que volte para a posicao inicial
}while(c0 != 0);
delay(800);
do{
  c2 = retornaPosicao();  // espera ate que realize a segunda posicao
}while(c2 == 0);
PiscaLed();
delay(800);
do{
  c0 = retornaPosicao();  // espera ate que volte para a posicao inicial
}while(c0 != 0);
delay(800);
do{
  c3 = retornaPosicao();  // espera ate que realize a terceira posicao
}while(c3 == 0);
PiscaLed();
delay(800);
do{
  c0 = retornaPosicao();  // espera ate que volte para a posicao inicial
}while(c0 != 0);
delay(800);

imprimeCaractere(c1,c2,c3); // envia a informacao das tres posicoes, cada posicao possui 4 possibilidades CIMA, DIREITA, BAIXO e ESQUERDA, totalizando um total de 64 possiveis caracteres
}

int retornaPosicao(){
  Wire.beginTransmission(MPU); // inicia a transmissao i2c
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);

  int AcXoff,AcYoff,AcZoff;

  // corrige os eixos do acelerometro
  AcXoff = -250;
  AcYoff = 36;

  // realiza a leitura do acelerometro com a correcao apllicada
  AcX=(Wire.read()<<8|Wire.read()) + AcXoff;
  AcY=(Wire.read()<<8|Wire.read()) + AcYoff;
  
  if(AcY > CIMA) // as possibilidades progridem em sentido horario
    return 1;
  else if(AcX < DIREITA)
    return 2;
  else if(AcY < BAIXO)
    return 3;
  else if(AcX > ESQUERDA)
    return 4;
  else
    return 0;
}

void imprimeCaractere(int cm1, int cm2, int cm3){
  if(cm1 == 1){
    if(cm2 == 1){
      if(cm3 == 1)
        Serial.print("A");
      if(cm3 == 2)
        Serial.print("B");
      if(cm3 == 3)
        Serial.print("C");
      if(cm3 == 4)
        Serial.print("D");
    }
    if(cm2 == 2){
      if(cm3 == 1)
        Serial.print("E");
      if(cm3 == 2)
        Serial.print("F");
      if(cm3 == 3)
        Serial.print("G");
      if(cm3 == 4)
        Serial.print("H");
    }
    if(cm2 == 3){
      if(cm3 == 1)
        Serial.print("I");
      if(cm3 == 2)
        Serial.print("J");
      if(cm3 == 3)
        Serial.print("K");
      if(cm3 == 4)
        Serial.print("L");
    }
    if(cm2 == 4){
      if(cm3 == 1)
        Serial.print("M");
      if(cm3 == 2)
        Serial.print("N");
      if(cm3 == 3)
        Serial.print("O");
      if(cm3 == 4)
        Serial.print("P");
    }
  }
  if(cm1 == 2){
    if(cm2 == 1){
      if(cm3 == 1)
        Serial.print("Q");
      if(cm3 == 2)
        Serial.print("R");
      if(cm3 == 3)
        Serial.print("S");
      if(cm3 == 4)
        Serial.print("T");
    }
    if(cm2 == 2){
      if(cm3 == 1)
        Serial.print("U");
      if(cm3 == 2)
        Serial.print("V");
      if(cm3 == 3)
        Serial.print("W");
      if(cm3 == 4)
        Serial.print("X");
    }
    if(cm2 == 3){
      if(cm3 == 1)
        Serial.print("Y");
      if(cm3 == 2)
        Serial.print("Z");
      if(cm3 == 3)
        Serial.print("0");
      if(cm3 == 4)
        Serial.print("1");
    }
    if(cm2 == 4){
      if(cm3 == 1)
        Serial.print("2");
      if(cm3 == 2)
        Serial.print("3");
      if(cm3 == 3)
        Serial.print("4");
      if(cm3 == 4)
        Serial.print("5");
    }
  }
  if(cm1 == 3){
    if(cm2 == 1){
      if(cm3 == 1)
        Serial.print("6");
      if(cm3 == 2)
        Serial.print("7");
      if(cm3 == 3)
        Serial.print("8");
      if(cm3 == 4)
        Serial.print("9");
    }
    if(cm2 == 2){
      if(cm3 == 1)
        Serial.print("-");
      if(cm3 == 2)
        Serial.print("-");
      if(cm3 == 3)
        Serial.print("-");
      if(cm3 == 4)
        Serial.print("-");
    }
    if(cm2 == 3){
      if(cm3 == 1)
        Serial.print("-");
      if(cm3 == 2)
        Serial.print("-");
      if(cm3 == 3)
        Serial.print("-");
      if(cm3 == 4)
        Serial.print("-");
    }
    if(cm2 == 4){
      if(cm3 == 1)
        Serial.print("-");
      if(cm3 == 2)
        Serial.print("-");
      if(cm3 == 3)
        Serial.print("-");
      if(cm3 == 4)
        Serial.print("-");
    }
  }
  if(cm1 == 4){
    if(cm2 == 1){
      if(cm3 == 1)
        Serial.print("-");
      if(cm3 == 2)
        Serial.print("-");
      if(cm3 == 3)
        Serial.print("-");
      if(cm3 == 4)
        Serial.print("-");
    }
    if(cm2 == 2){
      if(cm3 == 1)
        Serial.print("-");
      if(cm3 == 2)
        Serial.print("-");
      if(cm3 == 3)
        Serial.print("-");
      if(cm3 == 4)
        Serial.print("-");
    }
    if(cm2 == 3){
      if(cm3 == 1)
        Serial.print("-");
      if(cm3 == 2)
        Serial.print("-");
      if(cm3 == 3)
        Serial.print("-");
      if(cm3 == 4)
        Serial.print("-");
    }
    if(cm2 == 4){
      if(cm3 == 1)
        Serial.print("-");
      if(cm3 == 2)
        Serial.print("-");
      if(cm3 == 3)
        Serial.print("-");
      if(cm3 == 4)
        Serial.print("-");
    }
  }
}
