#include <Arduino.h>
#define entrada 26
#define salida 27
#define interrupcion 25

volatile bool bandera = 0;

void ISR_G25();

void setup() {
  //Configuración de puertos
  pinMode(entrada, INPUT_PULLUP);
  pinMode(salida, OUTPUT);
  pinMode(interrupcion, INPUT_PULLUP);

  //Interrupciones Externas
  attachInterrupt(digitalPinToInterrupt(interrupcion),ISR_G25,FALLING);
  
  
}

void loop() {
  if(bandera){
   digitalWrite(salida, digitalRead(entrada));
   bandera = false; 
  }
}

void ISR_G25(){
  bandera = true;
}
