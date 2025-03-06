#include "p18f4550.inc"	
     
  CONFIG  WDT = OFF          ;desactivo el watchdog para que no se detenga cuando entre en el bucle
  CONFIG  LVP = OFF         ;desactivo la opcion de sensibiladad de bajo voltaje
  
  ORG 0x00  ;fuerzo el inicio de la memoria en el espacio 0x00

  GOTO Inicio	    ;ir a la seccion del codigo de inicio 
  
Inicio:

    CLRF TRISA	    ;declaro los RA como salidas digitales
    CLRF LATA	    ;poner los RA en 0
    
;#######################################################
;		   PROGRAMA PRINCIPAL
;#######################################################
    
main:

    BSF LATA, RA0   ;enciendo RA0
    GOTO main	    ;vuelvo al inicio del ciclo 
    
END


