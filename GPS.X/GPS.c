#include "GPS.h"
#include "Config.h"
#include <string.h>

// Inicializaci�n del m�dulo GPS
void GPS_Init(void) {
    TRISC7 = 1;     // Configura RC7 como entrada (RX del GPS)
    
    // Configuraci�n del UART para 9600 baudios a 8MHz
    BAUDCON = 0x08; // BRG16 = 1 (modo 16 bits)
    TXSTA = 0x24;   // BRGH = 1, TXEN = 0 (solo recepci�n)
    RCSTA = 0x90;   // SPEN = 1, CREN = 1 (habilita UART y recepci�n continua)
    SPBRG = 207;    // Valor para 9600 baudios con BRG16=1 y BRGH=1
    
    // Limpieza inicial del buffer de recepci�n
    while (PIR1bits.RCIF) (void)RCREG;
    PIR1bits.RCIF = 0;
}

// Lee una frase NMEA desde el GPS
uint8_t GPS_ReadSentence(char *buffer, uint16_t max_len, uint16_t timeout_ms) {
    uint16_t i = 0;
    char c;
    uint8_t started = 0;

    // Reinicia la recepci�n UART
    RCSTAbits.CREN = 0;
    NOP();
    RCSTAbits.CREN = 1;
    
    // Limpia el buffer de recepci�n
    while (PIR1bits.RCIF) (void)RCREG;

    // Espera la llegada de datos con timeout
    for (uint16_t t = 0; t < timeout_ms; t++) {
        if (PIR1bits.RCIF) {
            c = RCREG;

            // Maneja error de sobreflujo
            if (RCSTAbits.OERR) {
                RCSTAbits.CREN = 0;
                RCSTAbits.CREN = 1;
                continue;
            }

            // Detecta inicio de frase NMEA
            if (!started && c == '$') {
                started = 1;
                buffer[i++] = c;
            } else if (started) {
                if (c == '\n' || i >= max_len - 1) {
                    buffer[i] = '\0';
                    return 1;
                }
                if (c != '\r') buffer[i++] = c;
            }
        }
        __delay_us(100);
    }
    return 0; // Timeout
}

// Parsea una frase GPRMC para extraer posici�n
uint8_t GPS_ParseGPRMC(const char *msg, char *lat, char *ns, char *lon, char *ew) {
    if (!strstr(msg, "$GPRMC")) return 0;

    char buf[100];
    strncpy(buf, msg, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    char *token = strtok(buf, ",");
    uint8_t field = 0;
    uint8_t data_valid = 0;

    while (token && field <= 6) {
        switch (field) {
            case 2:
                data_valid = (token[0] == 'A');
                break;
            case 3:
                if (lat && data_valid) {
                    strncpy(lat, token, 7);
                    lat[7] = '\0';
                }
                break;
            case 4:
                if (ns && data_valid) {
                    ns[0] = token[0];
                    ns[1] = '\0';
                }
                break;
            case 5:
                if (lon && data_valid) {
                    strncpy(lon, token, 8);
                    lon[8] = '\0';
                }
                break;
            case 6:
                if (ew && data_valid) {
                    ew[0] = token[0];
                    ew[1] = '\0';
                }
                break;
        }
        token = strtok(NULL, ",");
        field++;
    }
    return (data_valid && field >= 6);
}