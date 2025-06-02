// ==== LIBRERÍAS ====
#include <WiFi.h>             // Librería para conexión WiFi
#include <WebServer.h>        // Librería para crear un servidor web
#include <DHT.h>              // Librería para el sensor DHT11
#include <Wire.h>             // Librería para comunicación I2C (usada por el RTC)
#include "RTClib.h"           // Librería para manejar el RTC DS1307
#include <TinyGPS++.h>        // Librería para procesar datos NMEA del GPS

// ==== DEFINICIÓN DE PINES Y OBJETOS ====
#define DHTPIN 4              // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11         // Tipo de sensor DHT
DHT dht(DHTPIN, DHTTYPE);     // Crear objeto DHT

RTC_DS1307 rtc;               // Crear objeto para manejar el RTC
TinyGPSPlus gps;              // Crear objeto para manejar el GPS

// Seriales del ESP32 usados para el GPS y Bluetooth
HardwareSerial neogps(1);     // UART1: GPS (RX=16, TX=17)
HardwareSerial bt(2);         // UART2: Bluetooth (RX=25, TX=26)

// ==== CONFIGURACIÓN DE WIFI Y SERVIDOR WEB ====
const char* ssid = "ESP";           // Nombre de la red WiFi (puede ser AP o cliente)
const char* password = "12345678";  // Contraseña del WiFi
WebServer server(80);               // Crear servidor en el puerto 80 (HTTP)

// ==== VARIABLES GLOBALES ====
bool mostrarDatos = false;         // Bandera para decidir si se muestran datos (controlado por Bluetooth)
float temp = 0, hum = 0;           // Variables de temperatura y humedad
float tempMax = -1000, tempMin = 1000; // Inicialización para calcular máximos/mínimos
float humMax = -1000, humMin = 1000;
String horaStr = "--:--:--";       // Hora formateada como texto
String fechaStr = "--/--/----";    // Fecha formateada
String lat = "--", lng = "--", alt = "--"; // Datos GPS

// ==== PÁGINA HTML SERVIDA POR EL ESP32 ====
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html { font-family: Arial; text-align: center; background-color: #f2f2f2; }
    h2 { font-size: 2.2rem; margin-bottom: 10px; }
    .container { display: flex; justify-content: center; gap: 40px; flex-wrap: wrap; }
    .thermo-block { display: flex; flex-direction: column; align-items: center; margin-bottom: 20px; }
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
    .info { font-size: 1.1rem; margin-top: 10px; }
  </style>
</head>
<body>
  <h2>ESP32 - Monitoreo Ambiental</h2>

  <div class="container">
    <!-- Temperatura -->
    <div class="thermo-block">
      <div class="bar-wrapper">
        <div class="bar-container"><div class="bar-mask" id="temperature-mask" style="height: 100%;"></div></div>
        <div class="scale"><div>100</div><div>80</div><div>60</div><div>40</div><div>20</div><div>0</div></div>
      </div>
      <div class="label">🌡 Temperatura</div>
      <div class="value"><span id="temperature">--</span> °C</div>
      <div class="minmax">Máx: <span id="temperature-max">--</span> °C | Mín: <span id="temperature-min">--</span> °C</div>
    </div>

    <!-- Humedad -->
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

  <!-- Hora, Fecha y GPS -->
  <div class="label">🕒 Hora</div>
  <div class="value"><span id="hora">--:--:--</span></div>
  <div class="value"><span id="fecha">--/--/----</span></div>
  <div class="info">📡 Ubicación: <span id="lat">--</span>, <span id="lng">--</span> | Altitud: <span id="alt">--</span> m</div>

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
      document.getElementById('temperature-mask').style.height = (100 - Math.min(data.temp, 100)) + '%';
      document.getElementById('humidity-mask').style.height = (100 - Math.min(data.hum, 100)) + '%';
      document.getElementById('hora').textContent = data.hora;
      document.getElementById('fecha').textContent = data.fecha;
      document.getElementById('lat').textContent = data.lat;
      document.getElementById('lng').textContent = data.lng;
      document.getElementById('alt').textContent = data.alt;
    });
}
setInterval(updateData, 2000);
window.onload = updateData;
</script>
</body></html>
)rawliteral";
// ==== MANEJADOR PARA DEVOLVER DATOS SENSORIALES ====
void handleSensorData() {
  if (mostrarDatos) {
    // === Obtener hora y fecha del RTC ===
    DateTime now = rtc.now();
    horaStr = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
    fechaStr = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());

    // === Leer sensor DHT11 ===
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    if (!isnan(temp) && !isnan(hum)) {
      if (temp > tempMax) tempMax = temp;
      if (temp < tempMin) tempMin = temp;
      if (hum > humMax) humMax = hum;
      if (hum < humMin) humMin = hum;
    }

    // === Leer GPS ===
    if (gps.location.isValid()) {
      lat = String(gps.location.lat(), 6);
      lng = String(gps.location.lng(), 6);
      alt = String(gps.altitude.meters(), 2);
    } else {
      lat = lng = alt = "Sin señal";
    }
  }

  // === Enviar datos en formato JSON ===
  String json = "{";
  json += "\"temp\":" + String(temp, 1) + ",";
  json += "\"tempMax\":" + String(tempMax, 1) + ",";
  json += "\"tempMin\":" + String(tempMin, 1) + ",";
  json += "\"hum\":" + String(hum, 1) + ",";
  json += "\"humMax\":" + String(humMax, 1) + ",";
  json += "\"humMin\":" + String(humMin, 1) + ",";
  json += "\"hora\":\"" + horaStr + "\",";
  json += "\"fecha\":\"" + fechaStr + "\",";
  json += "\"lat\":\"" + lat + "\",";
  json += "\"lng\":\"" + lng + "\",";
  json += "\"alt\":\"" + alt + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

// ==== CONFIGURACIÓN INICIAL ====
void setup() {
  Serial.begin(115200);            // Comunicación con el PC
  dht.begin();                     // Iniciar sensor DHT
  Wire.begin(18, 19);              // Pines I2C para el RTC

  rtc.begin();                     // Iniciar el RTC
  if (!rtc.isrunning()) {
    Serial.println("RTC detenido, ajustando hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Poner hora del compilador
  }

  // Iniciar UARTs para GPS y Bluetooth
  neogps.begin(9600, SERIAL_8N1, 16, 17); // GPS en UART1
  bt.begin(9600, SERIAL_8N1, 25, 26);     // Bluetooth en UART2

  // Conectar a red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado. Dirección IP:");
  Serial.println(WiFi.localIP());

  // Configurar rutas del servidor web
  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", index_html); // Página HTML
  });
  server.on("/sensors", HTTP_GET, handleSensorData); // Datos JSON
  server.begin(); // Iniciar servidor
}

// ==== BUCLE PRINCIPAL ====
void loop() {
  server.handleClient();               // Manejar peticiones al servidor web

  while (neogps.available()) gps.encode(neogps.read()); // Procesar datos GPS

  if (bt.available())                  // Si llega un dato por Bluetooth
    mostrarDatos = (bt.read() == '0'); // Activar visualización si se recibe '0'
}
