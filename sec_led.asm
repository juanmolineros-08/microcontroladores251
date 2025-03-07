#include "p18f4550.inc"
  CONFIG  FOSC = INTOSC_HS      
  CONFIG  WDT = OFF             
  CONFIG  LVP = OFF             
  
  ORG 0x00
;#######################################################
;	    ASIGNAR MEMORIA A LAS VARIBLES
;#######################################################
;Entre las direcciones 0x20 y 0x30 son ligares libres y seguros para guardar 
;Las variables sin comprometer datos 
  ret Equ 0x21
  ret2 equ 0x22
  ret3 equ 0x23
  GOTO Inicio
;#######################################################
;		   INICIO DE PROGRAMA
;#######################################################
Inicio:
    MOVLW 0x72       ; Configurar el oscilador interno a 8MHz
    MOVWF OSCCON     
    CLRF TRISA       ; Configurar RA0 como salida
    
    BCF LATA, RA0    ; Asegurar que el LED inicie apagado
    BCF LATA, RA1    ; Asegurar que el LED inicie apagado
    BCF LATA, RA2    ; Asegurar que el LED inicie apagado
    BCF LATA, RA3    ; Asegurar que el LED inicie apagado

principal:
    
    CLRF LATA      ; Si RA0 est� apagado (0), salta la siguiente instrucci�n
    
    GOTO secuencia1     ; Si RA0 est� encendido (1), ir a apagar_led
  
    
;#######################################################
;	SUBRUTINAS PARA ENCENDER LOS LEDS
;#######################################################
    
secuencia1:
    BSF LATA, RA0    
    BSF LATA, RA1
    BSF LATA, RA2
    BSF LATA, RA3
    
    MOVLW 15
    CALL delay
    BCF LATA, RA0    
    BCF LATA, RA1
    BCF LATA, RA2
    BCF LATA, RA3
    
    MOVLW 4
    CALL delay 
    GOTO secuencia2
secuencia2:
    BSF LATA, RA0    
    BSF LATA, RA1
    
    MOVLW 15
    CALL delay
    BCF LATA, RA0    
    BCF LATA, RA1
    
    MOVLW 4
    CALL delay 
    GOTO secuencia3
secuencia3:
    BSF LATA, RA2
    BSF LATA, RA3
    
    MOVLW 15
    CALL delay
    BCF LATA, RA2
    BCF LATA, RA3
    
    MOVLW 4
    CALL delay 
    GOTO secuencia4
secuencia4:
    BSF LATA, RA0    
    BSF LATA, RA1
    BSF LATA, RA2
    BSF LATA, RA3
    
    MOVLW 15
    CALL delay
    BCF LATA, RA0    
    BCF LATA, RA1
    BCF LATA, RA2
    BCF LATA, RA3
    
    MOVLW 4
    CALL delay 
    GOTO secuencia5
secuencia5:
    BSF LATA, RA1
    BSF LATA, RA2
    
    MOVLW 15
    CALL delay
    BCF LATA, RA1
    BCF LATA, RA2
    
    MOVLW 4
    CALL delay 
    GOTO principal

    

;#######################################################
;	SUBRUTINA PARA GENERAR RETARDO VARIABLE
;#######################################################
    
;Este loop contiene 11 ciclos. El oscilaor interno funciona a 8MHz 

    
delay: 
    
    MOVWF ret		 ; Toma el valor que tiene almacenado w( 4 o 15 )
    
loop1:
    
    MOVLW 90		 ; Le damos otro valor a w para la iteracion
    MOVWF ret2		 ; Se lo asiganamos a la variable
    
loop2:
    
    MOVLW 255		 ; Le damos otro valor a w para la iteracion
    MOVWF ret3		 ; Se lo asiganamos a la variable  
    
loop:
    
    NOP			 ; Ciclo vacio 1
    NOP			 ; Ciclo vacio 1
    DECFSZ ret3		 ; Decrementa 255 hasta ser cero 1
    GOTO loop		 ; Si ret3 no ha llegado a cero se repite el ciclo 2
    DECFSZ ret2		 ; Cada deCremento de ret2 pasan 255 iteraciones de ret3 1
    GOTO loop2		 ; Si ret2 aun no llega a cero se repite desde el loop 2 2
    DECFSZ ret		 ; Cada iteracion de ret pasan 255x30 de los loops pasados 1
    GOTO loop1		 ; Si aun no es cero se repide desde el loop 1 1
    RETURN		 ; Devuelve a donde se llamo a la subrutina
    END
;#######################################################
;		    FIN DEL PROGRAMA
;#######################################################



