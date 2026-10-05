#include <Arduino.h>
#define entrada 25

volatile uint8_t cuenta = 0;
volatile uint8_t cuenta_actual = 0;

void ISR_G25();


void setup() {
  //Configuración de puertos
  pinMode(entrada, INPUT_PULLDOWN); //g25 ->Pull-Down
  //Inicializar Comunicación Serial
  Serial.begin(115200);
  //Configuración de Interrupciones Externas
  attachInterrupt(digitalPinToInterrupt(entrada), ISR_G25, RISING);
  Serial.println("¡Hola Mundo!");
  cuenta = 0; 
}

void loop() {  
  if(cuenta>15){
    cuenta = 0;
  } else if(cuenta != cuenta_actual){
    Serial.print("Cuenta");
    Serial.println(cuenta);
    cuenta_actual = cuenta;
  }  
}

void ISR_G25(){
  cuenta = cuenta+1; //cuenta++
}

