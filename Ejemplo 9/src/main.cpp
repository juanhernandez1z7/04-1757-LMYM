#include <Arduino.h>
#define LED 25

bool estadoLED = false; 
volatile bool bandera = false;
hw_timer_s *timer0 = NULL;

void IRAM_ATTR ISR_blink();

void setup() {
  //Configuración de pines
  pinMode(LED, OUTPUT);

  //Configuración de Timer
  timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, &ISR_blink,true);
  timerAlarmWrite(timer0, 500000, true);
  timerAlarmEnable(timer0);

  //Valor inicial 
  digitalWrite(LED, estadoLED);

}

void loop() {
  if(bandera){
    estadoLED = !estadoLED;
    digitalWrite(LED, estadoLED);
    bandera = false;
  }
}

void IRAM_ATTR ISR_blink(){
  bandera = true;
}