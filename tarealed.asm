; PIC18F4550 Configuration Bit Settings

; Assembly source line config statements

#include "p18f4550.inc"

; CONFIG1L
  CONFIG  PLLDIV = 1            ; PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
  CONFIG  CPUDIV = OSC1_PLL2    ; System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
  CONFIG  USBDIV = 1            ; USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

; CONFIG1H
  CONFIG  FOSC = INTOSC_EC      ; Oscillator Selection bits (Internal oscillator, CLKO function on RA6, EC used by USB (INTCKO))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

; CONFIG2L
  CONFIG  PWRT = OFF            ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  BOR = ON              ; Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
  CONFIG  BORV = 3              ; Brown-out Reset Voltage bits (Minimum setting 2.05V)
  CONFIG  VREGEN = OFF          ; USB Voltage Regulator Enable bit (USB voltage regulator disabled)

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = ON           ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
  CONFIG  PBADEN = OFF          ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = OFF           ; MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
  CONFIG  ICPRT = OFF           ; Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  ;DEFINICION DE VARIABLES
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
CBLOCK 0x20 ;Se inicia en el especio de memoria RAM
  contador1, contador2, contador3; Variables para calcular el retardo preciso de 5 seg
ENDC
  
ORG 0x0000 ;Direccion de inicio del programa
GOTO INICIO ;salta a la etiqueta inicio
  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;------------------------------------
;  PROGRAMA PRINCIPAL
;---------------------------------------
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
INICIO:
    MOVLW 0x72 ;IRCF = 111 (8mHZ), SCS = 10 (reloj interno) al work register
    MOVWF OSCCON, A ; pasa x72 al registro del oscilador, especificnando en banco de acceso de memoria
    CLRF TRISA, A ;configura puierto A como salidas
    CLRF LATA, A ;apaga todas las salidas del puerto A

;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    ;      BUCLE PRINCIPAL
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
BUCLE_PRINCIPAL:
    BTG LATA, RA0, A ;con btg se invierte el estado del bit 0 del puerto A
    CALL RETARDO ;va a la etiqueta retardo pero guarda la direcc del retorno
    BTG LATA, RA0, A ;como estaba encendido, se apaga al invertirlo nuevamente
    CALL RETARDO2 ; tiempo de apgado 2000 ms
    BRA BUCLE_PRINCIPAL ; usando BRA, mas economico que GOTO y sin guardar direcc de retorno

;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    ;SUBRUTINA GENERADORA DEL RETARDO 5000 ms
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
RETARDO:
    MOVLW   200                  ; Valor inicial para el contador1 (ajustado para 5 segundos)
    MOVWF   contador1, A
BUCLE1:
    MOVLW   255                  ; Valor inicial para el contador2
    MOVWF   contador2, A
BUCLE2:
    MOVLW   255                  ; Valor inicial para el contador3
    MOVWF   contador3, A
BUCLE3:
    NOP                          ; Instrucción No Operacion, consume 1 ciclo del reloj, para ajustar tiempo
    DECFSZ  contador3, F, A      ; Decrementa contador3, salta  la siguiente linea si es cero
    BRA     BUCLE3               ; Repite BUCLE3 si contador3 no es cero
    DECFSZ  contador2, F, A      ; Decrementa contador2, salta si es cero
    BRA     BUCLE2               ; Repite BUCLE2 si contador2 no es cero
    DECFSZ  contador1, F, A      ; Decrementa contador1, salta si es cero
    BRA     BUCLE1               ; Repite BUCLE1 si contador1 no es cero
    RETURN                       ; devuelve el retorno a la llamada CALL RETARDO
 
RETARDO2:
    MOVLW   164                  ; Valor inicial para el contador1 (ajustado para 2 segundos)
    MOVWF   contador1, A
BUCLE4:
    MOVLW   255                  ; Valor inicial para el contador2
    MOVWF   contador2, A
BUCLE5:
    MOVLW   255                  ; Valor inicial para el contador3
    MOVWF   contador3, A
BUCLE6:
    NOP                          ; Instrucción No Operacion, consume 1 ciclo del reloj, para ajustar tiempo
    DECFSZ  contador3, F, A      ; Decrementa contador3, salta  la siguiente linea si es cero
    BRA     BUCLE6               ; Repite BUCLE3 si contador3 no es cero
    DECFSZ  contador2, F, A      ; Decrementa contador2, salta si es cero
    BRA     BUCLE5               ; Repite BUCLE2 si contador2 no es cero
    DECFSZ  contador1, F, A      ; Decrementa contador1, salta si es cero
    BRA     BUCLE4               ; Repite BUCLE1 si contador1 no es cero
    RETURN                       ; devuelve el retorno a la llamada CALL RETARDO
    END ;Finaliza programa



