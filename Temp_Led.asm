#include "p18f4550.inc"	
    

  CONFIG  FOSC = INTOSC_HS ;declarar la activacion de la señal de reloj  
  CONFIG  WDT = OFF          ;desactivo el watchdog para que no se detenga cuando entre en el bucle
  CONFIG  LVP = OFF         ;desactivo la opcion de sensibiladad de bajo voltaje
  
  ORG 0x00  ;fuerzo el inicio de la memoria en el espacio 0x00
  
  var1 Equ 0x21	    ;declaro variable y donde se guarde 
  var2 equ 0x22	    ;declaro variable y donde se guarde 
  var3 equ 0x23	    ;declaro variable y donde se guarde 
  GOTO Inicio	    ;ir a la seccion del codigo de inicio 
  
Inicio:
    MOVLW 0x72	    ;declarar que usameros el oscilador de 8Mhz
    MOVWF OSCCON    ;lo guardo en la variable del oscilador
    CLRF TRISA	    ;declaro los RA como salidas digitales
    CLRF LATA	    ;poner los RA en 0
    
;#######################################################
;		   PROGRAMA PRINCIPAL
;#######################################################
    
main:

    BSF LATA, RA0   ;enciendo RA0
    CALL un_seg  ;llamo a un retardo de medio segundo
    CALL un_seg  ;llamo a un retardo de medio segundo
    CALL un_seg  ;llamo a un retardo de medio segundo
    CALL un_seg  ;llamo a un retardo de medio segundo
    CALL un_seg  ;llamo a un retardo de medio segundo
    BCF LATA, RA0   ;apago RA0
    CALL un_seg  ;llamo a un retardo de medio segundo
    CALL un_seg  ;llamo a un retardo de medio segundo
    GOTO main	    ;vuelvo al inicio del ciclo 
    

;#######################################################
;		   SECCION DE RETARDOS
;#######################################################
    
    
un_seg: 
    MOVLW 40
    MOVWF var1		 ;se guarda el valor anterior en la variable
    
loop1:
    
    MOVLW 255		 ; Le damos otro valor a w para la iteracion
    MOVWF var2		 ; Se lo asiganamos a la variable
    
loop2:
    
    MOVLW 255		 ; Le damos otro valor a w para la iteracion
    MOVWF var3		 ; Se lo asiganamos a la variable  
    
loop0:
    
    NOP			 ; Ciclo vacio
    DECFSZ var3		 ; Decrementa 255 hasta ser cero
    GOTO loop0		 ; Si ret3 no ha llegado a cero se repite el ciclo
    DECFSZ var2		 ; Cada deremento de ret2 pasan 255 iteraciones de ret3
    GOTO loop2		 ; Si ret2 aun no llega a cero se repite desde el loop 2
    DECFSZ var1		 ; Cada iteracion de ret pasan 255x30 de los loops pasados
    GOTO loop1		 ; Si aun no es cero se repide desde el loop 1
    RETURN		 ; Devuelve a donde se llamo a la subrutina
    END

;#######################################################
;		    FIN DEL PROGRAMA
;#######################################################



