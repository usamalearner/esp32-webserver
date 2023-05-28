#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WebServer server(80);

// Constant values for humidity and temperature
const float humidityValue = 50.0;
const float temperatureValue = 25.0;

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Humidity and Temperature</h1>";
  html += "<p>Click <a href='/humidity'>here</a> to view humidity.</p>";
  html += "<p>Click <a href='/temperature'>here</a> to view temperature.</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleHumidity() {
  String html = "<html><body>";
  html += "<h1>Humidity</h1>";
  html += "<p>Humidity: " + String(humidityValue) + "%</p>";
  html += "<p>Click <a href='/'>here</a> to go back.</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleTemperature() {
  String html = "<html><body>";
  html += "<h1>Temperature</h1>";
  html += "<p>Temperature: " + String(temperatureValue) + "°C</p>";
  html += "<p>Click <a href='/'>here</a> to go back.</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Handle root URL
  server.on("/", handleRoot);
  
  // Handle humidity URL
  server.on("/humidity", handleHumidity);
  
  // Handle temperature URL
  server.on("/temperature", handleTemperature);

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient();
}
