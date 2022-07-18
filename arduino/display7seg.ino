byte num = 0;

byte display7segmentos[36][7] =
			  //Pinos do Dislpay:{ A,B,C,D,E,F,G }
              //Pinos do Arduino:{ 3,4,5,6,7,8,9 }
								{{ 0,0,0,0,0,0,1 },  // = 0
                                 { 1,0,0,1,1,1,1 },  // = 1
                                 { 0,0,1,0,0,1,0 },  // = 2
                                 { 0,0,0,0,1,1,0 },  // = 3
                                 { 1,0,0,1,1,0,0 },  // = 4
                                 { 0,1,0,0,1,0,0 },  // = 5
                                 { 0,1,0,0,0,0,0 },  // = 6
                                 { 0,0,0,1,1,1,1 },  // = 7
                                 { 0,0,0,0,0,0,0 },  // = 8
                                 { 0,0,0,1,1,0,0 },  // = 9
  								 { 0,0,0,1,0,0,0 },  // = A
                                 { 1,1,0,0,0,0,0 },  // = b
                                 { 0,1,1,0,0,0,1 },  // = C
                                 { 1,0,0,0,0,1,0 },  // = d
                                 { 0,1,1,0,0,0,0 },  // = E
                                 { 0,1,1,1,0,0,0 },  // = F
                                 { 0,1,0,0,0,0,1 },  // = G
                                 { 1,1,0,1,0,0,0 },  // = h
                                 { 1,1,1,1,0,0,1 },  // = I
                                 { 1,0,0,0,0,1,1 },  // = J
                                 { 0,1,0,1,0,0,0 },  // = K
                                 { 1,1,1,0,0,0,1 },  // = L
                                 { 0,1,0,1,0,1,1 },  // = M
                                 { 0,0,0,1,0,0,1 },  // = N
                                 { 0,0,0,0,0,0,1 },  // = O
                                 { 0,0,1,1,0,0,0 },  // = P
                                 { 0,0,0,1,1,0,0 },  // = Q
                                 { 0,0,1,1,0,0,1 },  // = r
                                 { 0,1,0,0,1,0,0 },  // = S
                                 { 1,1,1,0,0,0,0 },  // = t
                                 { 1,0,0,0,0,0,1 },  // = U
                                 { 1,0,0,0,1,0,1 },  // = V
                                 { 1,0,1,0,1,0,1 },  // = W
                                 { 1,0,0,1,0,0,0 },  // = X
                                 { 1,0,0,0,1,0,0 },  // = Y
                                 { 0,0,1,0,1,1,0 }   // = Z
                               };

void setup() {                
  	pinMode(2, INPUT_PULLUP);
  	attachInterrupt(0, pressionaBotao, FALLING);
  
  	pinMode(3, OUTPUT);   
  	pinMode(4, OUTPUT);
  	pinMode(5, OUTPUT);
  	pinMode(6, OUTPUT);
  	pinMode(7, OUTPUT);
  	pinMode(8, OUTPUT);
  	pinMode(9, OUTPUT);
  	pinMode(10, OUTPUT);
}

void segmentos7(byte digito) {
  	byte pino = 3;
  	for (byte segmento = 0; segmento < 7; segmento++) {
    	digitalWrite(pino, display7segmentos[digito][segmento]);
    	pino++;
  	}
}

void loop() {
	segmentos7(num);
}

void pressionaBotao(){
	if(num <= 34)
	    num++;
	else
	    num=0;
}
