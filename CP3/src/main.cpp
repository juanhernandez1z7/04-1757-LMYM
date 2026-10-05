#include <Arduino.h>
#define A 33
#define B 25
#define C 26
#define D 27
#define entrada 32

volatile uint8_t contador = 0;
uint8_t fin_cuenta = 10;

// put function declarations here:
void cuenta();
void cuenta_LED(uint8_t cuenta);

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(entrada, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("Iniciando...");

  attachInterrupt(digitalPinToInterrupt(entrada), cuenta, RISING);
}

void loop() {
  if(contador <= fin_cuenta) {
    
    Serial.print("Cuenta: ");
    Serial.println(contador);
    cuenta_LED(contador);
    delay(250);
    contador++;
  }
  
}

// put function definitions here:
void cuenta() {
  contador=0;
}

void cuenta_LED(uint8_t cuenta){
  switch(cuenta) {
    case 0:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      break;
    case 1:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      break;
    case 2:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      break;
    case 3:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      break;
    case 4:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      break;
    case 5:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      break;
    case 6:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      break;
    case 7:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      break;
    case 8:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      break;
    case 9:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);  
  }
}