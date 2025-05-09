#ifndef DHT11_H
#define DHT11_H

#include <xc.h>
#include <stdint.h>
#include "Config.h"

#define DHT11_PIN  PORTAbits.RA0    // Pin DATA en RA0
#define DHT11_TRIS TRISAbits.TRISA0 

uint8_t DHT11_Read();
uint8_t DHT11_GetTemperature();

#endif