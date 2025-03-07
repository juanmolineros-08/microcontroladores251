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
    BCF LATA, RA1
    BCF LATA, RA2
    BCF LATA, RA3

principal:
    
    BTFSC LATA, RA0      ; Si RA0 est� apagado (0), salta la siguiente instrucci�n
    GOTO apagar_led      ; Si RA0 est� encendido (1), ir a apagar_led
    GOTO encender_led
    
;#######################################################
;	SUBRUTINA PARA ENCENDER EL LED POR 5S
;#######################################################
    
encender_led:
    
    MOVLW 29
    BSF LATA, RA0        ; Encender LED
    CALL delay           ; Esperar un tiempo
    GOTO principal	 ; Repetir el proceso
  
;#######################################################
;	SUBRUTINA PARA APAGAR EL LED POR 2S
;#######################################################
    
apagar_led: 
    
    MOVLW 12
    BCF LATA, RA0        ; Apagar LED
    CALL delay		 ; Esperar un tiempo
    GOTO principal       ; Repetir
    
;#######################################################
;	SUBRUTINA PARA GENERAR RETARDO VARIABLE
;#######################################################
    
;Este loop contiene 11 ciclos. El oscilaor interno funciona a 8MHz 
;Por tabto cada ciclo dura 2 Microsegundos, para obtener un retraso de 1s 
;Necesitamos en las tres iteraciones 6x30x255
;Si multiplciamos los 6x30x255 ciclos por el tiempo que toma un ciclo tenemos
;6x30x255x2 microsegundos, esto es igual a  a 1 segundo 
;Para un retraso de 2s necesitamos 12x30x255 y para 5s 30x30x255
    
delay: 
    
    MOVWF ret		 ; Toma el valor que tiene almacenado w( 12 o 30 )
    
loop1:
    
    MOVLW 30		 ; Le damos otro valor a w para la iteracion
    MOVWF ret2		 ; Se lo asiganamos a la variable
    
loop2:
    
    MOVLW 255		 ; Le damos otro valor a w para la iteracion
    MOVWF ret3		 ; Se lo asiganamos a la variable  
    
loop:
    
    NOP			 ; Ciclo vacio
    NOP			 ; Ciclo vacio
    DECFSZ ret3		 ; Decrementa 255 hasta ser cero
    GOTO loop		 ; Si ret3 no ha llegado a cero se repite el ciclo
    DECFSZ ret2		 ; Cada deCremento de ret2 pasan 255 iteraciones de ret3
    GOTO loop2		 ; Si ret2 aun no llega a cero se repite desde el loop 2
    DECFSZ ret		 ; Cada iteracion de ret pasan 255x30 de los loops pasados
    GOTO loop1		 ; Si aun no es cero se repide desde el loop 1
    RETURN		 ; Devuelve a donde se llamo a la subrutina
    END
;#######################################################
;		    FIN DEL PROGRAMA
;#######################################################




