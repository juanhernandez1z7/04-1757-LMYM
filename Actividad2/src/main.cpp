#include <Arduino.h>

#define entrada1  25
#define entrada2  26
#define salida1 27
#define salida2 33

void setup() {
  pinMode(entrada1, INPUT_PULLUP);
  pinMode(entrada2, INPUT_PULLUP);
  pinMode(salida2, OUTPUT);
  pinMode(salida1, OUTPUT);

}

void loop() {

  digitalWrite(salida1, !digitalRead(entrada1));
  digitalWrite(salida2, digitalRead(entrada2));
 
}