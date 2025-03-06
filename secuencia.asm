 ;PIC18F4550 Configuration Bit Settings

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
    
    CLRF TRISA     ; Configura RA como salida
    CLRF LATA          ; Asegura que el LED inicie apagado

    CBLOCK 0x20       ; Guarda  las variables en la memoria RAM  
        imp
        seg
        prim
        imp3
        seg3
        prim3
	imp2
        seg2
        prim2
	imp4
        seg4
        prim4
    ENDC
    
programa               
    CALL retardo05s ; llama a retardo de 0,5s
    BSF LATA, RA0   ; prende RA0
    BSF LATA, RA4   ; prende RA4 
    CALL retardo05s ; llama a retardo de 0,5s
    BCF LATA, RA0   ; apaga RA0
    BCF LATA, RA4   ; apaga RA4
    BSF LATA, RA1   ; prende RA1
    BSF LATA, RA3   ; prende RA3
    CALL retardo05s ; llama a retardo de 0,5s
    BCF LATA, RA1   ; apaga RA1
    BCF LATA, RA3   ; apaga RA3
    BSF LATA, RA2   ; prende RA2
    CALL retardo05s ; llama a retardo de 0,5s
    BCF LATA, RA2   ; apaga RA2
    CALL prendidos  ; prende todos 
    CALL apagados   ; apaga todos 
    GOTO programa   ; vuelve a la secuencia-
    

prendidos 
    MOVLW b'00011111' ; guarda en el registro 00011111 
    MOVWF PORTA       ; da los valores guardados al puerto A 
    CALL retardo4s    ; espera 4 segundos 
    RETURN
    
apagados 
    MOVLW b'00000000' ; guarda en el registro 00000000 
    MOVWF PORTA       ; da los valores guardados al puerto A 
    CALL retardo2s    ; espera 2 segundos 
    RETURN
    


retardo2s      
    MOVLW d'19' 
    MOVWF imp2 
rg3
    MOVLW d'255'
    MOVWF seg2  
rg2
    MOVLW d'255'
    MOVWF prim2 
retardo2 
    DECFSZ prim2, F    
    GOTO retardo2    
    DECFSZ seg2 , F     
    DECFSZ imp2 , F    
    GOTO rg3         
    
    RETURN           
    
   
    
retardo05s       
    MOVLW d'5'  
    MOVWF imp3  
rg5
    MOVLW d'255'
    MOVWF seg3  
rg4
    MOVLW d'255'
    MOVWF prim3 
retardo3 
    DECFSZ prim3 , F    
    GOTO retardo3    
    DECFSZ seg3 , F     
    GOTO rg4         
    DECFSZ imp3 , F     
    GOTO rg5        
    RETURN         
    
retardo4s 
    MOVLW d'24'
    MOVWF imp4 
rg8
    MOVLW d'255'
    MOVWF seg4
rg7
    MOVLW d'255'
    MOVWF prim4 
retardo4 
    DECFSZ prim4 , F
    GOTO retardo4
    DECFSZ seg4 , F
    GOTO rg7
    DECFSZ imp4 , F
    GOTO rg8
    
    RETURN
    
  END
 
    
    
    
   
    
    
    


