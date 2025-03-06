#include "p18f4550.inc"
  CONFIG  FOSC = INTOSC_HS      
  CONFIG  WDT = OFF             
  CONFIG  LVP = OFF             
  
  ORG 0x00

  GOTO Inicio
;#######################################################
;		   INICIO DE PROGRAMA
;#######################################################
Inicio:
    
    BCF TRISA, RA0       ; Configurar RA0 como salida
    BCF LATA, RA0        ; Asegurar que el LED inicie apagado
    BSF LATA, RA0        ; Encender LED

    END
    
;#######################################################
;		    FIN DEL PROGRAMA
;#######################################################



