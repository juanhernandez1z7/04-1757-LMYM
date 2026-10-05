#include <Arduino.h>
#define entrada_1 25
#define entrada_2 26

volatile int8_t cuenta = 0;
volatile int8_t cuenta_actual = 0;

void ISR_G25();
void ISR_G26();


void setup() {
  //Configuración de puertos
  pinMode(entrada_1, INPUT_PULLDOWN); //g25 ->Pull-Down
  pinMode(entrada_2, INPUT_PULLDOWN); //g26 ->Pull-Down
  //Inicializar Comunicación Serial
  Serial.begin(115200);
  //Configuración de Interrupciones Externas
  attachInterrupt(digitalPinToInterrupt(entrada_1), ISR_G25, RISING);
  attachInterrupt(digitalPinToInterrupt(entrada_2), ISR_G26, FALLING);
  Serial.println("¡Hola Mundo!");
  cuenta = 0; 
  Serial.print("Cuenta: ");
  Serial.println(cuenta);
}

void loop() {  
  if(cuenta>15){
    cuenta = 0;
  } else if(cuenta<0){
    cuenta = 15;
  } else if(cuenta != cuenta_actual){
    Serial.print("Cuenta");
    Serial.println(cuenta);
    cuenta_actual = cuenta;
  }  
}

void ISR_G25(){
  cuenta = cuenta+1; //cuenta++
}

void ISR_G26(){
  cuenta = cuenta-1; //cuenta--
}

