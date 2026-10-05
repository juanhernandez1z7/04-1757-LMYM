#include <Arduino.h>
// Declaración de constantes ⚡❤️📆
#define A 35
#define B 27
#define x 33
#define y 34
#define z 25

void setup() {
  //Declaración de puertos
  pinMode(A, INPUT_PULLDOWN);
  pinMode(B, INPUT_PULLDOWN);
  pinMode(x, INPUT_PULLDOWN);
  pinMode(y, INPUT_PULLDOWN);
  pinMode(z, OUTPUT);  
}

void loop() {
  bool leer_A = digitalRead(A);
  bool leer_B = digitalRead(B);
  uint8_t op = leer_A*2 + leer_B;

  bool leer_x = digitalRead(x);
  bool leer_y = digitalRead(y);

  bool salida = 0;

  if(op == 0){
    salida = leer_x & leer_y;
  }else if(op == 1){
    salida = leer_x | leer_y;
  }else if(op == 2){
    salida = !leer_y;
  }else{
    salida = leer_x ^ leer_y;
  }

  digitalWrite(z,salida);
}
