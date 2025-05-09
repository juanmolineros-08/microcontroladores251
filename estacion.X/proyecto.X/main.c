#include <stdio.h>
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "Config.h"
#include "LCD.h"
#include "DHT11.h"
#include "ds1307.h"
#include "i2c.h"




void mostrar_temperatura(void) {
    OSCCON = 0x72;          // Oscilador a 8MHz
    TRISAbits.TRISA0 = 1;   // RA0 como entrada
    ADCON1 = 0x0F;          // Pines AN como digitales
    CMCON = 0x07;           // Deshabilitar comparadores

    LCD_Init();             // Inicializar LCD
    LCD_Clear();            // Limpiar pantalla
    LCD_String_xy(0, 0, "Temperatura:"); // Texto completo

    while(1) {
        uint8_t temp = DHT11_GetTemperature();
        
        if (temp != 255) {
            char buffer[6];
            // Formato: "24 C"
            buffer[0] = (temp/10) + '0';  // Decenas
            buffer[1] = (temp%10) + '0';  // Unidades
            buffer[2] = ' ';
            buffer[3] = 'C';
            buffer[4] = '\0';
            
            LCD_String_xy(1, 0, buffer);  // Mostrar en segunda fila
        } else {
            LCD_String_xy(1, 0, "Error "); 
        }
        __delay_ms(2000);
    }
}

void mostrar_rtc(void) {
  unsigned char h, m, s, d, mo, y;
    char buffer[17];

    OSCCONbits.IRCF = 0b111; // 8 MHz
    OSCCONbits.SCS = 0b10;
    ADCON1 = 0x0F;

    LCD_Init();
    LCD_Clear();
    I2C_Master_Init(100000); // MSSP I2C en RB0/RB1
    LCD_String_xy(0, 0, "Configurando RTC");
    RTC_Init();
    RTC_SetDateTime(14, 30, 0, 8, 4, 25); // Configuración inicial
    LCD_Clear();
    while (1) {        
        RTC_GetDateTime(&h, &m, &s, &d, &mo, &y);
        
        sprintf(buffer, "Fecha:%02d/%02d/20%02d", d, mo, y);
        LCD_String_xy(0, 0, buffer);

        // Mostrar hora con prefijo "Hora:"
        sprintf(buffer, "Hora: %02d:%02d:%02d", h, m, s);
        LCD_String_xy(1, 0, buffer);

        __delay_ms(1000);
    }
}

   // Inicializaciones
void main(void) {
    TRISD = 0x00;
    LATD = 0x00;
    // Inicializaciones
    LCD_Init();
    RTC_Init();

    while (1) {
        // Leer datos del sensor DHT11
      

        // Mostrar temperatura
        mostrar_temperatura();
        __delay_ms(2000);  // Espera 2 segundos

        // Mostrar hora y fecha del RTC
        mostrar_rtc();
        __delay_ms(3000);  // Espera 3 segundos
    }
}