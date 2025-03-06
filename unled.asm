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
    BSF LATA, RA0      ; Prende el LED EN RA0 


END 
