
; PIC18F4550 Configuration Bit Settings

; Assembly source line config statements
      

#include "p18f4550.inc"
    
    CONFIG  FOSC = INTOSC_HS      ; Oscillator Selection bits (Internal oscillator, HS oscillator used by USB (INTHS))
    CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
    CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
    CONFIG PLLDIV = 1
    CONFIG CPUDIV = OSC1_PLL2
    CONFIG USBDIV = 2
    CONFIG FCMEN = OFF 
    CONFIG IESO = OFF
    
    ORG 0x00
    
     ; Configuración del oscilador interno
    MOVLW 0x72         ; Configura el oscilador a 8MHz (OSCCON = 01110010)
    MOVWF OSCCON
    
    BCF TRISA, RA0     ; Configura RA0 como salida
    CLRF LATA          ; Asegura que el LED inicie apagado

    CBLOCK 0x20  ; guarda las variables en la RAM       
        imp
        seg
        prim
	imp2
        seg2
        prim2
    ENDC
    
    
programa
    BSF LATA, RA0 ; PRENDE EL LED 
    CALL retardo5s ; MANTIENE PRENDIDO EL LED DURANTE 5S
    BCF LATA, RA0 ; APAGA EL LED 
    CALL retardo2s ; MANTIENE APAGADO EL LED DURANTE 2S 
    GOTO programa 
    
    
retardo5s 
    MOVLW d'40' ; carga el valor 40 (en binario) en el registro w
    MOVWF imp   ; Asigna el valor de 40 (en binario) a la variable img 
rg1
    MOVLW d'255' ; carga el valor 255 (en binario) en el registro w
    MOVWF seg    ; Asigna el valor de 255 (en binario) a la variable img 
rg
    MOVLW d'255'  ; carga el valor 255 (en binario) en el registro w
    MOVWF prim    ; Asigna el valor de 255 (en binario) a la variable prim 
retardo 
    DECFSZ prim , F ; resta 1 al valor de prim hasta que este sea cero 
    GOTO retardo    ; va de nuevo a retardo para seguir restando 1 a prim hasta que sea 0 y se salte esta linea 
    DECFSZ seg , F  ; resta 1 al valor de seg hasta que este sea cero, va guardando este resultado en la misma variable seg 
    GOTO rg         ; va a rg y guarda el valor de 255 en prim cada vez que se le resta 1 a seg y el resultado no es 0. Cuando sea cero se saltara esta linea  
    DECFSZ imp, F   ; resta imp al valor de seg hasta que este sea 0, va guardando el resultado en la misma variable imp 
    GOTO rg1        ; va a rg1 y guarda el valor de 255 en seg cada vez que se le resta 1 a imp y el resultado no es 0. Cuando sea cero se saltara esta linea
    
    RETURN ; vuelve a donde se hizo el llamado de retardo5s
    
            ; calculo de los ciclos de cada linea 
retardo2s   ;   2 cm por el llamado anterior
    MOVLW d'19'  ;   1cm
    MOVWF imp2  ;   1cm
rg3
    MOVLW d'255';   1cm * imp2
    MOVWF seg2  ;   1cm * imp2
rg2
    MOVLW d'255';   1cm *imp2 * seg2
    MOVWF prim2 ;   1cm *imp2 * seg2
retardo2 
    DECFSZ prim2, F    ; imp2 * seg2[(prim2-1)+2]
    GOTO retardo2    ; imp2 * seg2 [2*(prim2-1)]
    DECFSZ seg2 , F     ; imp2[(seg2-1)+2]
    GOTO rg2         ; imp2 [2*(seg2-1)]
    DECFSZ imp2 , F     ; (imp2-1)+2
    GOTO rg3         ;  2*(imp2-1)
    
    RETURN           ;2cm

    
  END
 
    
    
    
   
    
    
    