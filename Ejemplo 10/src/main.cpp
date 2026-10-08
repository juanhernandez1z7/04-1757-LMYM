#include <Arduino.h>
#define PIN_INTERRUPCION 25
#define LED0 26
#define LED1 27

uint8_t LED[2] = {LED1, LED0};
uint8_t estado[2] = {0, 0};

volatile bool bandera_INT = false;
volatile bool bandera_TIMER = false;

uint8_t cuenta = 0;
hw_timer_s *timer0 = NULL;

uint32_t retardo = 250000;


void IRAM_ATTR ISR_T0();
void IRAM_ATTR ISR_G25();
void mostrarCuenta(uint8_t valor);

void setup() {
  //Configuración de puertos
  for(uint8_t i = 0; i<sizeof(LED)/sizeof(LED[0]); i++){
    pinMode(LED[i], OUTPUT);
  }
  pinMode(PIN_INTERRUPCION, INPUT_PULLUP);

  //Interrupciones Externas
  attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPCION), ISR_G25,RISING);

  //Configuración de T0
  timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, &ISR_T0, true);
  timerAlarmWrite(timer0, retardo, true);
  timerAlarmEnable(timer0);

  //Valor Inicial
  mostrarCuenta(cuenta);
}

void loop() {
  if(bandera_INT){
    retardo = (retardo==100000)? 250000 : 1000000;
    bandera_INT = false;
  }
  if(bandera_TIMER){ 
    if(cuenta == 3){
      cuenta = 0;
    }else{
      cuenta++;
    }
    mostrarCuenta(cuenta);
    bandera_TIMER = false;
  }
}

void mostrarCuenta(uint8_t valor){
  switch (valor) {
    case 0: 
      estado[1] = 0;
      estado[0] = 0;
    break;
    case 1: 
      estado[1] = 0;
      estado[0] = 1;
    break;
    case 2: 
      estado[1] = 1;
      estado[0] = 0;
    break;
    case 3: 
      estado[1] = 1;
      estado[0] = 1;
    break;
  }

  for(uint8_t i = 0; i<sizeof(LED)/sizeof(LED[0]); i++){
    digitalWrite(LED[i], estado[i]);
  }
}

void IRAM_ATTR ISR_T0(){
  bandera_TIMER = true;
  timerAlarmWrite(timer0, retardo, true);
  timerAlarmEnable(timer0);  
}

void IRAM_ATTR ISR_G25(){
  bandera_INT = true;
}

