#include <DHT.h>
#include <Wire.h>
#include "RTClib.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
  dht.begin();

  Wire.begin(21, 22); // SDA, SCL

  if (!rtc.begin()) {
    Serial.println("No se encontró el RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC no está corriendo, ajustando hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.println("Sistema iniciado correctamente");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  DateTime now = rtc.now();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Error al leer el DHT11");
  } else {
    Serial.print("Hora: ");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.print(now.second());

    Serial.print(" | Temp: ");
    Serial.print(temp);
    Serial.print(" °C");

    Serial.print(" | Humedad: ");
    Serial.print(hum);
    Serial.println(" %");
  }

  delay(2000);
}