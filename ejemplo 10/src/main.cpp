/* 
  Diseñe un programa que realice una cuenta del 0 al 3 de manera ascendente, con un retardo de 250 ms; sin embargo 
  cuando haya una interrupción externa en GPIO25 (sensible a flanco de bajada), cambie su valor a 1000 ms. 
  Cuando vuelva a ocurrir la interrupción, vuelva a 500 ms. La cuenta no debe parar
*/

#include <Arduino.h>
#define INTERRUPT_PIN 25
#define LED 25

volatile int delayTime = 250;
volatile bool bandera_tiempo = false;
hw_timer_t * timer0 = NULL;
uint8_t cuenta = 0;

void IRAM_ATTR interrupcion() {
  bandera_tiempo = !bandera_tiempo;
}

void IRAM_ATTR int_tiempo(){
}


void mostrarCuenta(uint8_t valor){
  switch (valor) {
    case 0:
      digitalWrite(LED, LOW);
      break;
    case 1:
      digitalWrite(LED, HIGH);
      break;
    case 2:
      digitalWrite(LED, LOW);
      break;
    case 3:
      digitalWrite(LED, HIGH);
      break;
    default:
      break;
  }
}

void setup() {
  
  pinMode(LED, OUTPUT);

  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), interrupcion, FALLING);

  timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, &int_tiempo, true);
  timerAlarmWrite(timer0, delayTime * 1000, true);
  timerAlarmEnable(timer0);

}

void loop() {
  if (bandera_tiempo) {
    delayTime = 1000;
  } else {
    delayTime = 250;
  }

  if(cuenta >3){
    cuenta = 0;
  }else{
    cuenta++;
    mostrarCuenta(cuenta);
  }

  
}

