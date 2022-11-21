#include <WiFi.h> //Conexão WiFi
#include <HTTPClient.h> //Requisições Http
#include <string> //Importa o tipo de variavel string

const char* ssid = "exemploNOME"; //Nome da rede
const char* password = "exemploSENHA"; //Senha da rede
const char* ip = "exemploIP" ;

String serverName = "http://" + ip + ":1234/registro/insert"; //Endpoint de POST utilizando o Ipv4 do cliente atual

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

//Inicia o WiFi
void iniciaWifi(){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  //enquanto o wifi não for conectado ele fica na espera e printando "..." no serial, assim que ele conectar ele confirma a conecção e diz o IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado na rede Wifi com o enderaço de IP: ");
  Serial.println(WiFi.localIP());
}

//Recebe os valores dos sensores e joga para o banco através do Http
void alimentarBanco(float umidade, float temperatura, String horario, int estufa) {
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
      Serial.println("{\"Temperatura\":" + String(temperatura) + ", \"Umidade\":" + 
      String(umidade) + ",\"Horario\":" + String(horario) + ",\"id_estufa\":" + String(estufa) + "}");
      // Free resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}