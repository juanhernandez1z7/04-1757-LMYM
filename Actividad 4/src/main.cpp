#include <Arduino.h>
#define A 25
#define B 26
#define C 27

#define INT1 32
#define INT2 33

//definimos los vectores para los pines y estados 
uint8_t LED[3] = {A, B, C};
uint8_t estados[3] = {0, 0, 0};
int8_t cuenta = 0;

volatile bool bandera_tiempo = false;
volatile bool secuencia = true; //true->ascendente, false-> descendente

hw_timer_s *timer0 = NULL;

void mostrarCuenta();
void ISR_G25();
void ISR_G26();
void ISR_retardo();


void setup() {
    //Configuración de puertos
    for(uint8_t i = 0; i<sizeof(LED)/sizeof(LED[0]); i++){
        pinMode(LED[i], OUTPUT);
    }
    pinMode(INT1, INPUT_PULLUP);
    pinMode(INT2, INPUT_PULLUP);
    
    //Configuración de Interrupciones Externas
    attachInterrupt(digitalPinToInterrupt(INT1), ISR_G25, RISING);
    attachInterrupt(digitalPinToInterrupt(INT2), ISR_G26, FALLING);

    //Configuración de Interrupciones por timer0
    timer0 = timerBegin(0, 80, true);
    timerAttachInterrupt(timer0, &ISR_retardo, true);
    timerAlarmWrite(timer0, 250000, true);
    timerAlarmEnable(timer0);

    //Valor Inicial
    mostrarCuenta();
}

void loop() {
    if(bandera_tiempo){
        if(secuencia){
            cuenta++;
           if(cuenta>7) {
                cuenta = 0;
           }
            mostrarCuenta();
           
        }else{
            cuenta--;
            if(cuenta<0) {                
                cuenta = 7;
           }
            mostrarCuenta();
           
        }

        bandera_tiempo = false;
    }  
}

void IRAM_ATTR ISR_G25(){
    secuencia = false;
}

void IRAM_ATTR ISR_G26(){
    secuencia = true;
}

void IRAM_ATTR ISR_retardo(){
    bandera_tiempo = true;
}

void mostrarCuenta(){
    switch (cuenta){
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
        default:
            estados[2] = 0;
            estados[1] = 0;
            estados[0] = 0;
        break;
    }

    for(uint8_t i = 0; i<sizeof(LED)/sizeof(LED[0]); i++){
        digitalWrite(LED[i], estados[i]);
    }


}

