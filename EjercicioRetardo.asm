#include <p18f4550.inc>
    CONFIG FOSC = INTOSC_EC       ; Oscilador interno (8 MHz)
    CONFIG WDT = OFF              ; WDT deshabilitado
    CONFIG PBADEN = OFF           ; PBADEN deshabilitado
    CONFIG LVP = OFF              ; Programación en bajo voltaje deshabilitada


    CBLOCK 0x30
	OUTER       ; Contador para el bucle externo
	MIDDLE      ; Contador para el bucle medio
	INTER       ; Contador para el bucle interno
    ENDC

    ORG 0x00 ;Forzar a inicar en la direccion 0x00 y vector de reset
    GOTO main

main:
    CLRF    TRISB         ; Configura PORTB como salida
    CLRF    LATB          ; Apaga todos los LEDs

Loop:
    ; Enciende el LED1 en RB0 durante 5 segundos
    BSF     LATB, 0       ; Enciende LED (RB0 = 1)
    CALL    Delay1S       ; Retardo ? 1 segundo
    CALL    Delay1S       ; ? 2 segundos
    CALL    Delay1S       ; ? 3 segundos
    CALL    Delay1S       ; ? 4 segundos
    CALL    Delay1S       ; ? 5 segundos
    BCF     LATB, 0       ; Apaga LED (RB0 = 0)

    ; Apaga el LED durante 2 segundos
    CALL    Delay1S       ; ? 1 segundo
    CALL    Delay1S       ; ? 2 segundos

    GOTO    Loop          ; Repite la secuencia


Delay1S: ;Subrutina : Aproximadamente 1 segundo de retardo
	MOVLW   10 
	MOVWF   OUTER
;CALCULOS : Iteraciones totales: 10 x 100 x 200 = 200,000.
; Si cada iteración consume ~10 ciclos, se generan 2,000,000 ciclos,
; lo que a 0.5 µs por ciclo da ?1 segundo.
DelayOuter:
	MOVLW   0x64 
	MOVWF   MIDDLE
DelayMiddle:
	MOVLW   0xC8
	MOVWF   INTER
DelayInner:
	NOP			; Consume 1 ciclo
	DECFSZ  INTER, F	;Decrementa a INTER , salta si llega a 0
	GOTO    DelayInner
	DECFSZ  MIDDLE, F	;Decrementa a MIDDLE, salta si llega a 0
	GOTO    DelayMiddle 
	DECFSZ  OUTER, F	;Decrementa a OUTER, salta si llega a 0
	GOTO    DelayOuter
	RETURN

    END



