#include "p18f4550.inc"	;declaro el PIC usado
    

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
    BSF LATA, RA1   ;enciendo RA1
    CALL medio_seg  ;llamo a un retardo de medio segundo
    CALL on_off	    ;llamo al alternador
    CALL on_off	    ;llamo al alternador
    CALL on_off	    ;llamo al alternador
    CALL on_off	    ;llamo al alternador
    CALL medio_seg  ;llamo a un retardo de medio segundo
    BSF LATA, RA2   ;enciendo RA0
    BSF LATA, RA3   ;enciendo RA1
    CALL medio_seg  ;llamo a un retardo de medio segundo
    CALL on_off	    ;llamo al alternador
    CALL on_off	    ;llamo al alternador
    CALL on_off	    ;llamo al alternador
    BSF LATA, RA0   ;enciendo RA0
    BSF LATA, RA2   ;enciendo RA1
    CALL medio_seg  ;llamo a un retardo de medio segundo
    CALL on_off	    ;llamo al alternador
    CALL on_off	    ;llamo al alternador
    CALL on_off	    ;llamo al alternador
    CLRF LATA	    ;pongo toda la fila de RA en 0
    CALL medio_seg  ;llamo al retardo de un segundo
    GOTO main	    ;vuelvo al inicio del ciclo 
    
    
;#######################################################
;		SECCION DE ALTERNADOS
;#######################################################
    
on_off: 
    
    BTG LATA, RA0   ;alterno el estado de RA3
    BTG LATA, RA1   ;alterno el estado de RA3
    BTG LATA, RA2   ;alterno el estado de RA3
    BTG LATA, RA3   ;alterno el estado de RA3
    CALL medio_seg  ;llamo a un retardo de medio segundo
    RETURN

;#######################################################
;		   SECCION DE RETARDOS
;#######################################################
    
    
medio_seg: 
    MOVLW 20
    MOVWF var1		 ; Toma el valor que tiene almacenado 
    
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
