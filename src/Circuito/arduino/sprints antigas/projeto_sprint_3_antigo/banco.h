#include <WiFi.h>
#include <HTTPClient.h>

// const char* ssid = "Inteli-COLLEGE";
// const char* password = "QazWsx@123";
const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";

String serverName = "http://10.128.65.207:1234/registro/insert";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void iniciaWifi(){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void alimentarBanco(float umidade, float temperatura, float horario, int estufa) {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"Temperatura\":" + String(temperatura) + ", \"Umidade\":" + 
      String(umidade) + ",\"Horario\":" + String(horario) + ",\"id_estufa\":" + String(estufa) + "}");
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      // Free resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}