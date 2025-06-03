#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Wire.h>
#include "RTClib.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;

const char* ssid = "SANTIAGO";
const char* password = "ximesanty";

WebServer server(80);

float temp = 0, hum = 0;
float tempMax = -1000, tempMin = 1000;
float humMax = -1000, humMin = 1000;
String hora = "--:--:--";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html { font-family: Arial; text-align: center; background-color: #f2f2f2; }
    h2 { font-size: 2.2rem; margin-bottom: 30px; }
    .container { display: flex; justify-content: center; gap: 40px; flex-wrap: wrap; }
    .thermo-block { display: flex; flex-direction: column; align-items: center; margin-bottom: 30px; }
    .bar-wrapper { display: flex; flex-direction: row; align-items: flex-end; gap: 8px; }
    .bar-container {
      position: relative; width: 60px; height: 250px;
      background: linear-gradient(to top, #0000ff, #00ffff, #00ff00, #ffff00, #ff0000);
      border-radius: 30px; overflow: hidden; border: 2px solid #999;
    }
    .bar-mask {
      position: absolute; top: 0; width: 100%;
      background: rgba(0, 0, 0, 0.5);
      transition: height 0.5s; z-index: 1;
    }
    .scale {
      display: flex; flex-direction: column; justify-content: space-between;
      height: 250px; font-size: 0.9rem;
    }
    .label { margin-top: 10px; font-size: 1.2rem; font-weight: bold; }
    .value { font-size: 1.4rem; margin-top: 5px; }
    .minmax { font-size: 1rem; margin-top: 4px; color: #333; }
    .clock { font-size: 1.8rem; margin: 20px 0; font-weight: bold; }
  </style>
</head>
<body>
  <h2>ESP32 Monitor de Temperatura, Humedad y Hora</h2>
  
  <div class="label">🕒 Hora</div>
  <div class="value"><span id="hora">--:--:--</span></div>
  <div class="value"><span id="fecha">--/--/----</span></div>

  <div class="container">
    <!-- Termómetro de Temperatura -->
    <div class="thermo-block">
      <div class="bar-wrapper">
        <div class="bar-container"><div class="bar-mask" id="temperature-mask" style="height: 100%;"></div></div>
        <div class="scale"><div>100</div><div>80</div><div>60</div><div>40</div><div>20</div><div>0</div></div>
      </div>
      <div class="label">🌡 Temperatura</div>
      <div class="value"><span id="temperature">--</span> °C</div>
      <div class="minmax">Máx: <span id="temperature-max">--</span> °C | Mín: <span id="temperature-min">--</span> °C</div>
    </div>

    <!-- Termómetro de Humedad -->
    <div class="thermo-block">
      <div class="bar-wrapper">
        <div class="bar-container"><div class="bar-mask" id="humidity-mask" style="height: 100%;"></div></div>
        <div class="scale"><div>100</div><div>80</div><div>60</div><div>40</div><div>20</div><div>0</div></div>
      </div>
      <div class="label">💧 Humedad</div>
      <div class="value"><span id="humidity">--</span> %</div>
      <div class="minmax">Máx: <span id="humidity-max">--</span> % | Mín: <span id="humidity-min">--</span> %</div>
    </div>
  </div>

<script>
function updateData() {
  fetch('/sensors')
    .then(response => response.json())
    .then(data => {
      document.getElementById('temperature').textContent = data.temp.toFixed(1);
      document.getElementById('temperature-max').textContent = data.tempMax.toFixed(1);
      document.getElementById('temperature-min').textContent = data.tempMin.toFixed(1);
      document.getElementById('humidity').textContent = data.hum.toFixed(1);
      document.getElementById('humidity-max').textContent = data.humMax.toFixed(1);
      document.getElementById('humidity-min').textContent = data.humMin.toFixed(1);
      document.getElementById('clock').textContent = data.hora;

      document.getElementById('temperature-mask').style.height = (100 - Math.min(data.temp, 100)) + '%';
      document.getElementById('humidity-mask').style.height = (100 - Math.min(data.hum, 100)) + '%';
      document.getElementById('hora').textContent = data.hora;
      document.getElementById('fecha').textContent = data.fecha;
    });
}
setInterval(updateData, 2000);
window.onload = updateData;
</script>
</body>
</html>
)rawliteral";

void handleSensorData() {
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  if (!isnan(temp) && !isnan(hum)) {
    if (temp > tempMax) tempMax = temp;
    if (temp < tempMin) tempMin = temp;
    if (hum > humMax) humMax = hum;
    if (hum < humMin) humMin = hum;
  }

  DateTime now = rtc.now();

String fecha = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
String hora = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

String json = "{";
json += "\"temp\":" + String(temp, 1) + ",";
json += "\"tempMax\":" + String(tempMax, 1) + ",";
json += "\"tempMin\":" + String(tempMin, 1) + ",";
json += "\"hum\":" + String(hum, 1) + ",";
json += "\"humMax\":" + String(humMax, 1) + ",";
json += "\"humMin\":" + String(humMin, 1) + ",";
json += "\"hora\":\"" + hora + "\",";
json += "\"fecha\":\"" + fecha + "\"";
json += "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  Wire.begin(18, 19);
  if (!rtc.begin()) {
    Serial.println("No se encontró el RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC detenido, ajustando hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado. Dirección IP:");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", index_html);
  });
  server.on("/sensors", HTTP_GET, handleSensorData);
  server.begin();
}

void loop() {
  server.handleClient();
}

