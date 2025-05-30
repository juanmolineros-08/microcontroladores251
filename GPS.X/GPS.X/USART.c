

#include "USART.h"


void USART_Init(long baud_rate)
{
    float temp;
    TRISC6 = 0;  // TX como salida
    TRISC7 = 1;  // RX como entrada
    temp = Baud_value;
    SPBRG = (int)temp;
    TXSTA = 0x20;  // Habilita transmisi�n
    RCSTA = 0x90;  // Habilita recepci�n y el puerto serial
}

void USART_TxChar(char out)
{
    while (TXIF == 0);  // Espera a que TXREG est� listo
    TXREG = out;
}

char USART_RxChar()
{
    while (RCIF == 0);  // Espera recepci�n
    if (RCSTAbits.OERR) {
        CREN = 0;
        NOP();
        CREN = 1;
    }
    return RCREG;
}

void USART_SendString(const char *out)
{
    while (*out != '\0') {
        USART_TxChar(*out++);
    }
}

/*****************************USART por software*******************************/
void SoftUSART_Init()
{
    SOFT_TX_TRIS = 0;  // TX como salida
    SOFT_RX_TRIS = 1;  // RX como entrada
    SOFT_TX_PIN = 1;   // L�nea en reposo
}

void SoftUSART_TxChar(char data)
{
    char i;
    SOFT_TX_PIN = 0;  // Bit de inicio
    __delay_us(SOFT_BIT_DELAY_US);

    for (i = 0; i < 8; i++) {
        SOFT_TX_PIN = (data >> i) & 1;
        __delay_us(SOFT_BIT_DELAY_US);
    }

    SOFT_TX_PIN = 1;  // Bit de parada
    __delay_us(SOFT_BIT_DELAY_US);
}

char SoftUSART_RxChar()
{
    char i, data = 0;

    while (SOFT_RX_PIN);  // Esperar bit de inicio (l�nea baja)

    __delay_us(SOFT_BIT_DELAY_US + SOFT_BIT_DELAY_US / 2);  // Centrar lectura

    for (i = 0; i < 8; i++) {
        if (SOFT_RX_PIN)
            data |= (1 << i);
        __delay_us(SOFT_BIT_DELAY_US);
    }

    // Bit de parada
    __delay_us(SOFT_BIT_DELAY_US);

    return data;
}

void SoftUSART_SendString(const char *str)
{
    while (*str != '\0') {
        SoftUSART_TxChar(*str++);
    }
}