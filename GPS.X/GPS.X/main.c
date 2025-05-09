#include <xc.h>
#include "Config.h"
#include "LCD.h"
#include "USART.h"



void main(void) {
    LCD_Port = 0x00;
    TRISD = 0x00; // LCD en PORTD
    LCD_Init();
    USART_Init(9600); // Inicializa el USART con 9600 baudios

    LCD_String_xy(0, 0, "Bluetooth LCD");

    while (1) {
        char dato = USART_RxChar();

        if (dato == '1') {
            LATDbits.LATD3 = 1; // Supongamos que RD3 controla el backlight
            LCD_Clear();
            LCD_String_xy(0, 0, "LCD Encendida");
        } else if (dato == '0') {
            LATDbits.LATD3 = 0;
            LCD_Clear();
            LCD_String_xy(0, 0, "LCD Apagada");
        } else if (dato == 'T') {
            LCD_Clear();
            LCD_String_xy(0, 0, "Texto desde cel");
        } else {
            LCD_Clear();
            LCD_String_xy(0, 0, "Comando?");
        }
    }
}
