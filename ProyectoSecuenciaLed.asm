#include <p18f4550.inc> 
;CONFIGURACION DE BITS
    CONFIG FOSC = INTOSC_EC       ; Oscilador interno
    CONFIG WDT = OFF              ; Watchdog Timer deshabilitado
    CONFIG PBADEN = OFF           ; PBADEN deshabilitado
    CONFIG LVP = OFF              ; Programación en bajo voltaje deshabilitada


    CBLOCK 0x20
	MYLED       ; Rutina para encender LED correspondiente
	D1          ; Contador externo para Delay1S
	D2          ; Contador interno para Delay1S
	OUTER       ; Contador del bucle externo para Delay1S
	MIDDLE      ; Contador del bucle medio para Delay1S
	INTER       ; Contador del bucle interno para Delay1S
    ENDC

    ORG 0x00 ;Forzar a iniciar en la direccion 0x00 y vector reset
    
   ;CONFIGURACION OSCILADOR INTERNO
    MOVLW 0x72 ; Configuracion para que prendan los leds a la hora de montarlo en fisico
    MOVWF OSCCON
    
    CLRF    TRISA       ; Configura PORTA como salida (todos 0 = salida)
    CLRF    LATA         ; Apaga todos los LEDs inicialmente


main_loop:
    ; LED0 en RA0 : 2 segundos
    BSF LATA, 0           ; Enciende LED0-RA0
    CALL Delay1S          ; Llama a delay de 1 segundo
    CALL Delay1S          ; Llama a delay de 1 segundo (cumple 2 s en total)
    BCF LATA, 0           ; Apaga LED0-RA0

    ; LED1 en RA1: 1 segundo
    BSF LATA, 1           ; Enciende LED1-RA1
    CALL Delay1S          ; Delay de 1 segundo (cumple 1 segundo en total)
    BCF LATA, 1           ; Apaga LED1-RA1

    ; LED2 en RA2: 3 segundos
    BSF LATA, 2           ; Enciende LED2-RA2
    CALL Delay1S          ; 1 s
    CALL Delay1S          ; 2 s
    CALL Delay1S          ; 3 s (durar 3 segundos en total)
    BCF LATA, 2           ; Apaga LED2-RA2

    ; LED3 en RA3: 2 segundos
    BSF LATA, 3           ; Enciende LED3-RA3
    CALL Delay1S          ; 1 s
    CALL Delay1S          ; 2 s (duracion 2 segundos en total)
    BCF LATA, 3           ; Apaga LED3-RA3

    ; LED4 en RA4: 1 segundo
    BSF LATA, 4           ; Enciende LED4-RA4
    CALL Delay1S          ; 1 s
    BCF LATA, 4           ; Apaga LED4-RA4

    ; LED5 en RA5: 2 segundos
    BSF LATA, 5           ; Enciende LED5-RA5
    CALL Delay1S          ; 1 s
    CALL Delay1S          ; 2 s (duracion 2 segundos en total)
    BCF LATA, 5           ; Apaga LED5-RA5

    GOTO main_loop        ; Repite la secuencia


Delay1S: ; Delay1S: Subrutina de retardo aproximado de 1 segundo
	MOVLW 10           ; OUTER = 10
	MOVWF OUTER
; Cálculo: 10 * 100 * 200 = 200,000 iteraciones. 
; Si cada iteración consume ~ 10 ciclos, se generan 2,000,000 ciclos,
; que a 0.5 µs cada uno dan aproximadamente 1 segundo.
DelayOuter:
	MOVLW 0x64          ; MIDDLE = 100 (64 en hexadecimal)
	MOVWF MIDDLE
DelayMiddle:
	MOVLW 0xC8          ; INTER = 200 (C8 en hexadecimal)
	MOVWF INTER
DelayInner:
    NOP                ; 1 ciclo
    DECFSZ INTER, F    ; Decrementa INTER, salta si llega a 0
    GOTO DelayInner
    DECFSZ MIDDLE, F   ; Decrementa MIDDLE, repite si no es 0
    GOTO DelayMiddle
    DECFSZ OUTER, F    ; Decrementa OUTER, repite si no es 0
    GOTO DelayOuter
    RETURN

    END



