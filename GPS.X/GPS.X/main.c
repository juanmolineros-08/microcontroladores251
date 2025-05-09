/*
 * File:   main.c
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:14 PM
 */


/*
 * File:   main.c
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:14 PM
 */

/*
 * File:   main.c
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:14 PM
 */

#include <xc.h>
#include "Config.h"
#include "LCD.h"
#include "GPS.h"
#include <string.h>

void MostrarCoordenadas(const char* lat, const char* ns, const char* lon, const char* ew) {
    char formatted_lat[16] = {0};
    char formatted_lon[16] = {0};

    // Formatea la latitud: DD°MM.MM' N/S
    snprintf(formatted_lat, sizeof(formatted_lat), "%.2s\xDF%.5s' %s", lat, lat + 2, ns);

    // Formatea la longitud: DDD°MM.MM' E/W
    snprintf(formatted_lon, sizeof(formatted_lon), "%.3s\xDF%.4s' %s", lon, lon + 3, ew);

    LCD_Clear();
    LCD_String_xy(0, 0, "Lat:");
    LCD_String_xy(0, 5, formatted_lat);
    LCD_String_xy(1, 0, "Lon:");
    LCD_String_xy(1, 5, formatted_lon);
}

void main(void) {
    OSCCON = 0x72;
    LCD_Init();
    LCD_String_xy(0, 0, "GPS GPRMC");
    __delay_ms(2000);

    GPS_Init();

    // Buffers
    char buffer[100];
    char lat[10] = "";
    char ns[2]  = "";
    char lon[11] = "";
    char ew[2]  = "";
    uint8_t datos_validos = 0;

    while(1) {
        // Limpia los buffers
        memset(buffer, 0, sizeof(buffer));
        lat[0] = ns[0] = lon[0] = ew[0] = '\0';

        // Lee una frase NMEA válida
        if (GPS_ReadSentence(buffer, sizeof(buffer), 1000) && strstr(buffer, "$GPRMC")) {
            if (GPS_ParseGPRMC(buffer, lat, ns, lon, ew)) {
                MostrarCoordenadas(lat, ns, lon, ew);
                datos_validos = 1;
                __delay_ms(500);
                continue;
            }
        }

        if (datos_validos) {
            __delay_ms(100);
        } else {
            LCD_Clear();
            LCD_String_xy(0, 0, "Buscando...");
            __delay_ms(500);
        }
    }
}