#include <p18f4550.inc>
;--------------------------------------------
; Configuración de Fusibles
;--------------------------------------------
    CONFIG FOSC = INTOSC_EC       ; Oscilador interno (8 MHz) con función CLKO en RA6
    CONFIG WDT = OFF              ; Watchdog Timer deshabilitado
    CONFIG PBADEN = OFF           ; PORTB digital en reset
    CONFIG LVP = OFF              ; Programación en bajo voltaje deshabilitada


    CBLOCK 0x20
	MYLED       ; Patrón para encender el LED correspondiente
	D1          ; Contador externo para Delay1S
	D2          ; Contador interno para Delay1S
	OUTER       ; Contador del bucle externo para Delay1S
	MIDDLE      ; Contador del bucle medio para Delay1S
	INNER       ; Contador del bucle interno para Delay1S
    ENDC

;--------------------------------------------
; Vector de Reset y Ubicación del Código
;--------------------------------------------
    ORG 0x00
    
    ;Configuracion oscilador interno
    MOVLW 0x72
    MOVWF OSCCON
    
    CLRF    TRISA       ; Configura PORTB como salida (todos 0 = salida)
    CLRF    LATA         ; Apaga todos los LEDs inicialmente


main_loop:
    ; LED en RB0: 2 segundos
    BSF LATA, 0           ; Enciende LED RB0
    CALL Delay1S          ; Llama a delay de 1 segundo
    CALL Delay1S          ; Llama a delay de 1 segundo (2 s en total)
    BCF LATA, 0           ; Apaga LED RB0

    ; LED en RB1: 1 segundo
    BSF LATA, 1           ; Enciende LED RB1
    CALL Delay1S          ; Delay de 1 segundo
    BCF LATA, 1           ; Apaga LED RB1

    ; LED en RB2: 3 segundos
    BSF LATA, 2           ; Enciende LED RB2
    CALL Delay1S          ; 1 s
    CALL Delay1S          ; 2 s
    CALL Delay1S          ; 3 s
    BCF LATA, 2           ; Apaga LED RB2

    ; LED en RB3: 2 segundos
    BSF LATA, 3           ; Enciende LED RB3
    CALL Delay1S          ; 1 s
    CALL Delay1S          ; 2 s
    BCF LATA, 3           ; Apaga LED RB3

    ; LED en RB4: 1 segundo
    BSF LATA, 4           ; Enciende LED RB4
    CALL Delay1S          ; 1 s
    BCF LATA, 4           ; Apaga LED RB4

    ; LED en RB5: 2 segundos
    BSF LATA, 5           ; Enciende LED RB5
    CALL Delay1S          ; 1 s
    CALL Delay1S          ; 2 s
    BCF LATA, 5           ; Apaga LED RB5

    GOTO main_loop        ; Repite la secuencia

;-----------------------------------------------------------
; Delay1S: Subrutina de retardo aproximado de 1 segundo
; Suponiendo: 
;   - Oscilador interno de 8 MHz (1 ciclo de instrucción = 0.5 µs)
; Usamos tres bucles anidados:
;   OUTER = 10, MIDDLE = 100, INNER = 200
; Cálculo: 10 * 100 * 200 = 200,000 iteraciones. 
; Si cada iteración consume ~10 ciclos, se generan 2,000,000 ciclos,
; que a 0.5 µs cada uno dan aproximadamente 1 segundo.
;-----------------------------------------------------------
Delay1S:
	MOVLW 10           ; Outer = 10
	MOVWF OUTER
DelayOuter:
	MOVLW 0x64          ; Middle = 100
	MOVWF MIDDLE
DelayMiddle:
	MOVLW 0xC8          ; Inner = 200
	MOVWF INNER
DelayInner:
    NOP                ; 1 ciclo
    DECFSZ INNER, F    ; Decrementa INNER, salta si llega a 0
    GOTO DelayInner
    DECFSZ MIDDLE, F   ; Decrementa MIDDLE, repite si no es 0
    GOTO DelayMiddle
    DECFSZ OUTER, F    ; Decrementa OUTER, repite si no es 0
    GOTO DelayOuter
    RETURN

    END



