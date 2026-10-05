#include <Arduino.h>
#define ascendente 25
#define descendente 26

#define A 16
#define B 17
#define C 18
#define D 19

uint8_t salidas[4] = {A, B, C, D};
uint8_t estados[4];

volatile bool bandera_asc = 0;
volatile bool bandera_desc = 0;

void ISR_G25();
void ISR_G26();
void cuenta(uint8_t cuenta);

void setup() {
  //Configuración de puertos
  pinMode(ascendente, INPUT_PULLUP);
  pinMode(descendente, INPUT_PULLUP);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);

  //Inicializar Comunicación serial
  Serial.begin(115200);

  //Interrupciones Externas
  attachInterrupt(digitalPinToInterrupt(ascendente),ISR_G25,FALLING);
  attachInterrupt(digitalPinToInterrupt(descendente),ISR_G26,FALLING);
  
  
}

void loop() {
  if(bandera_asc){
    for(uint8_t i = 0; i<=15; i++){
      Serial.println(i);
      cuenta(i);
      delay(250);
    }
  }
  if(bandera_desc){
    for(uint8_t i = 15; i>=0; i--){
      Serial.println(i);
      cuenta(i);
      delay(250);
    }
  }
  
}

void ISR_G25(){
  bandera_asc = true;
}

void ISR_G26(){
  bandera_desc = true;
}

void cuenta(uint8_t cuenta){
  switch (cuenta){
  case 0:
    estados[0] = 0;
    estados[1] = 0;
    estados[2] = 0;
    estados[3] = 0;
  break;

  case 1:
    estados[0] = 0;
    estados[1] = 0;
    estados[2] = 0;
    estados[3] = 1;
  break;

  case 2:
    estados[0] = 0;
    estados[1] = 0;
    estados[2] = 1;
    estados[3] = 0;
  break;

  case 3:
    estados[0] = 0;
    estados[1] = 0;
    estados[2] = 1;
    estados[3] = 1;
  break;

  case 4:
    estados[0] = 0;
    estados[1] = 0;
    estados[2] = 0;
    estados[3] = 0;
  break;

  case 5:
    estados[0] = 0;
    estados[1] = 1;
    estados[2] = 0;
    estados[3] = 1;
  break;

  case 6:
    estados[0] = 0;
    estados[1] = 1;
    estados[2] = 1;
    estados[3] = 0;
  break;

  case 7:
    estados[0] = 0;
    estados[1] = 1;
    estados[2] = 1;
    estados[3] = 1;
  break;

  case 8:
    estados[0] = 1;
    estados[1] = 0;
    estados[2] = 0;
    estados[3] = 0;
  break;

  case 9:
    estados[0] = 1;
    estados[1] = 0;
    estados[2] = 0;
    estados[3] = 1;
  break;

  case 10:
    estados[0] = 1;
    estados[1] = 0;
    estados[2] = 1;
    estados[3] = 0;
  break;

  case 11:
    estados[0] = 1;
    estados[1] = 0;
    estados[2] = 1;
    estados[3] = 1;
  break;

  case 12:
    estados[0] = 1;
    estados[1] = 1;
    estados[2] = 0;
    estados[3] = 0;
  break;

  case 13:
    estados[0] = 1;
    estados[1] = 1;
    estados[2] = 0;
    estados[3] = 1;
  break;

  case 14:
    estados[0] = 1;
    estados[1] = 1;
    estados[2] = 1;
    estados[3] = 0;
  break;

  case 15:
    estados[0] = 1;
    estados[1] = 1;
    estados[2] = 1;
    estados[3] = 1;
  break;
  
  default:
  
    estados[0] = 0;
    estados[1] = 0;
    estados[2] = 0;
    estados[3] = 0;
  
    break;
  }


  for(uint8_t i=0; i<sizeof(estados) / sizeof(estados[0]); i++){
    digitalWrite(salidas[i], estados[i]);
  }

}