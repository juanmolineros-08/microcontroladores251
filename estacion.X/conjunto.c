#include <stdio.h>
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "Config.h"
#include "LCD.h"
#include "DTH11.h"
#include "ds1307.h"
#include "USART.h"

#define _XTAL_FREQ 8000000

// ------------------- NUEVO: variables globales -------------------
uint8_t sistema_activo = 0;
uint8_t estado = 0; // 0 = Temp, 1 = Hora, 2 = GPS



void mostrar_temperatura(void) {
    uint8_t temp = DHT11_GetTemperature();
    char buffer[16];
    LCD_Clear();
    sprintf(buffer, "Temp: %u C", temp);
    LCD_String_xy(0, 0, buffer);
}

void mostrar_rtc(void) {
    unsigned char h, m, s, d, mo, y;
    char fecha[17], hora[17];
    RTC_GetDateTime(&h, &m, &s, &d, &mo, &y);

    sprintf(hora, "Hora: %02u:%02u:%02u", h, m, s);
    sprintf(fecha, "Fecha: %02u/%02u/%02u", d, mo, y);
    LCD_Clear();
    LCD_String_xy(0, 0, hora);
    LCD_String_xy(1, 0, fecha);
}

// ------------------- NUEVO: función de interrupción -------------------
void __interrupt() ISR(void) {
    // Interrupción por recepción vía Bluetooth (USART)
    if (PIR1bits.RCIF) {
        char comando = RCREG;  // leer carácter recibido

        // Manejo de error de overrun
        if (RCSTAbits.OERR) {
            CREN = 0;
            NOP();
            CREN = 1;
        }

        if (comando == '1') {
            sistema_activo = 1;
        } else if (comando == '0') {
            sistema_activo = 0;
            LCD_Clear();
            LCD_String_xy(0, 0, "Sistema en pausa");
        }

        PIR1bits.RCIF = 0; // Limpiar bandera (opcional)
    }

    // Interrupción externa INT2 (RB2)
    if (INTCON3bits.INT2IF) {
        // Alternar estado del sistema
        sistema_activo ^= 1;

        if (sistema_activo) {
            LCD_Clear();
            LCD_String_xy(0, 0, "Sistema activo");
            
        } else {
            LCD_Clear();
            LCD_String_xy(0, 0, "Sistema en pausa");
        }

        INTCON3bits.INT2IF = 0; // Limpiar bandera
    }
}


void main(void) {
    // Inicializaciones
    LCD_Init();
    DHT11_Read();
    RTC_Init();
    
    USART_Init(9600);

    // ------------------ NUEVO: habilitar interrupciones ------------------
    TRISBbits.TRISB2 = 1;              // RB2 como entrada
    INTCON2bits.INTEDG2 = 1;           // Flanco ascendente (1) o descendente (0)
    INTCON3bits.INT2IF = 0;            // Limpiar bandera INT2
    INTCON3bits.INT2IE = 1;            // Habilitar interrupción INT2
    INTCONbits.PEIE = 1;     // habilita interrupciones periféricas
    INTCONbits.GIE = 1;      // habilita interrupciones globales
    PIE1bits.RCIE = 1;       // habilita interrupción del USART RX
    INTCONbits.INT0IE = 1; // Enable INT0
    INTCONbits.INT0IF = 0; // Clear interrupt flag
    INTCON2bits.INTEDG0 = 0; // Interrupt on falling edge of RB0
    LCD_String_xy(0,0,"MICROCONTROL");
    __delay_ms(2000);
    LCD_Clear();
    __delay_ms(1000);

    while (1) {
        if (sistema_activo) {
            mostrar_temperatura();
            __delay_ms(1000);
            mostrar_rtc();
            __delay_ms(3000); // Espera 3 segundos
        } else {
            LCD_String_xy(0,0,"apagado"); // Reduce carga si está inactivo
        }
    }
}
