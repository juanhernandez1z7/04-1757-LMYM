#include <Arduino.h>
#define entrada 25
uint8_t cuenta = 0;
uint8_t finCuenta = 15;


void setup() {
  pinMode(entrada, INPUT_PULLDOWN);
  Serial.begin(115200);
  Serial.println("¡Hola Mundo!");
}

void loop() {
  bool lectura = digitalRead(entrada);
  if(lectura){
    cuenta++;
    if(cuenta > finCuenta){
      cuenta = 0;
    }

    Serial.print("Cuenta: ");
    Serial.println(cuenta);
    delay(512);
  }
 
}

