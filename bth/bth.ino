#include <TinyGPS++.h>
#include <DHT.h>
#include <Wire.h>
#include "RTClib.h"

#define DHTPIN 4
#define DHTTYPE DHT11

TinyGPSPlus gps;
DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;

// UARTs
HardwareSerial neogps(1); // GPS
HardwareSerial bt(2);     // Bluetooth

bool mostrarDatos = false;

void setup() {
  Serial.begin(115200);

  // DHT11
  dht.begin();

  // RTC
  Wire.begin(18, 19);
  if (!rtc.begin()) {
    Serial.println("No se encontró el RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC detenido, ajustando hora...");
      }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // GPS
  neogps.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17

  // Bluetooth
  bt.begin(9600, SERIAL_8N1, 25, 26);     // RX=25, TX=26
  Serial.println("Sistema listo");
}

void loop() {
  // Leer datos del GPS (para tener datos actualizados)
  while (neogps.available()) {
    gps.encode(neogps.read());
  }

  // Leer Bluetooth
  if (bt.available()) {
    char comando = bt.read();

    if (comando == '0') {
      mostrarDatos = true;
    } else {
      mostrarDatos = false;
    }
  }

  // Mostrar datos o no
  if (mostrarDatos) {
    // RTC
    DateTime now = rtc.now();

    // DHT
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    Serial.print("Hora: ");
    Serial.print(now.hour()); Serial.print(":");
    Serial.print(now.minute()); Serial.print(":");
    Serial.print(now.second());

    Serial.print(" | Temp: ");
    Serial.print(temp);
    Serial.print(" °C");

    Serial.print(" | Humedad: ");
    Serial.print(hum);
    Serial.println(" %");

    if (gps.location.isValid()) {
      Serial.print("Latitud: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitud: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("Altitud: ");
      Serial.print(gps.altitude.meters());
      Serial.println(" m");
    } else {
      Serial.println("GPS sin señal");
    }

    Serial.println("-----------------------------");
  } else {
    Serial.println("APAGADO");
  }

  delay(2000);
}


