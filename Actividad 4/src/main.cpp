#include <Arduino.h>

#define A 25 
#define B 26
#define C 27
#define PIN_INT_ASC 32
#define PIN_INT_DES 33

uint8_t LED [3] = {A, B, C};
uint8_t estados[3] = {0,0,0};
int8_t cuenta = 0;

volatile bool cuentaDireccion = false;
volatile bool banderaTiempo = false;


hw_timer_s *timer0 = NULL;

void IRAM_ATTR ISR_ASC(){
  cuentaDireccion = true;
}

void IRAM_ATTR ISR_DES(){
  cuentaDireccion = false;
}

void IRAM_ATTR Timer0 (){
  banderaTiempo = true;
}

void mostrarCuenta();


void setup() {
  //Declaración de pines
  for(uint8_t i = 0; i<sizeof(LED)/sizeof(LED[0]); i++){
    pinMode(LED[i], OUTPUT);
  }

  pinMode(PIN_INT_ASC, INPUT_PULLUP);
  pinMode(PIN_INT_DES, INPUT_PULLUP);

  //Configuración de Interrupciones Externas
  attachInterrupt(digitalPinToInterrupt(PIN_INT_ASC), ISR_ASC, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_INT_DES), ISR_DES, FALLING);

  //Configuración de Timer
  timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, &Timer0, true);
  timerAlarmWrite(timer0, 500000, true);
  timerAlarmEnable(timer0);

  Serial.begin(115200);
  //Valor inicial
  mostrarCuenta();
  Serial.print("Cuenta: ");
  Serial.println(cuenta);
    
}

void loop() {
  //BanderaTiempo
  if(banderaTiempo){
    if(cuentaDireccion){
      cuenta++;
      if(cuenta > 7){
        cuenta = 0;
      }      
      mostrarCuenta();
    }else{
      cuenta--;
      if(cuenta < 0){
        cuenta = 7;
      }
      mostrarCuenta();
    }
    Serial.print("Cuenta: ");
    Serial.println(cuenta);
    banderaTiempo = false;
  }
  
}

void mostrarCuenta(){
  switch(cuenta){
    case 0: 
      estados[2] = 0;
      estados[1] = 0;
      estados[0] = 0;
    break;

    case 1: 
      estados[2] = 0;
      estados[1] = 0;
      estados[0] = 1;
    break;

    case 2: 
      estados[2] = 0;
      estados[1] = 1;
      estados[0] = 0;
    break;

    case 3: 
      estados[2] = 0;
      estados[1] = 1;
      estados[0] = 1;
    break;

    case 4: 
      estados[2] = 1;
      estados[1] = 0;
      estados[0] = 0;
    break;

    case 5: 
      estados[2] = 1;
      estados[1] = 0;
      estados[0] = 1;
    break;

    case 6: 
      estados[2] = 1;
      estados[1] = 1;
      estados[0] = 0;
    break;

    case 7: 
      estados[2] = 1;
      estados[1] = 1;
      estados[0] = 1;
    break;
  }

  for(uint8_t i = 0; i<sizeof(LED)/sizeof(LED[0]); i++){
    digitalWrite(LED[i], estados[i]);
  }
}

