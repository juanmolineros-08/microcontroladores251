#include <p18f4550.inc>
    CONFIG FOSC = INTOSC_EC       ; Oscilador interno (8 MHz) 
    CONFIG WDT = OFF              ; Watchdog Timer deshabilitado
    CONFIG PBADEN = OFF           ;PBADEN deshabilitado
    CONFIG LVP = OFF              ; Programación en bajo voltaje deshabilitada

    ORG 0x00 ;Forzar a iniciar en direccion 0x00
    GOTO main

main:
    CLRF    TRISB             ; Configura PORTB como salida (todos los pines en 0 = salida)
    CLRF    LATB              ; Apaga todos los LEDs

    BSF     LATB, 0           ; Prende el LED conectado a RB0 (pone el bit 0 en 1)
    BCF     LATB, 0           ; Apaga el LED (pone el bit 0 en 0)

    END





