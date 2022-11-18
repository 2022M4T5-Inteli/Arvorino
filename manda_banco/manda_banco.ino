//Importação de arquivos com função de o que cada componente deve fazer
#include <Wire.h>               //Gerencia a comunicação entre os dispositivos através do protocolo I2C
#include <Adafruit_AHT10.h>     //Sensor AHT10
#include <LiquidCrystal_I2C.h>  //Display lcd
#include <string>               //Inclui o tipo de variável string
#include <WiFi.h>               //Conexão WiFi
#include <HTTPClient.h>         //Requisições Http

const char* ssid = "Inteli-COLLEGE"; //Nome da rede
const char* password = "QazWsx@123"; //Senha da rede

String serverName = "http://10.128.0.24:1234/registro/insert"; //Endpoint de POST utilizando o Ipv4 do cliente atual

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

//------------------------------------------------CONECTA NO WIFI----------------------------------------------------------------------------//

//Inicia o WiFi
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

//-------------------------------------------------POST DOS VALORES PARA O BANCO----------------------------------------------------------------------------//

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

//Variaveis para as portas
const int ledVermelho = 40;
const int ledVerde = 38;
const int ledAzul = 37;
#define sdaPin 4
#define sclPin 6
float tempValor = 0;
float umidValor = 0;

// Endereço do LCD e número de colunas e linhas do display
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
Adafruit_AHT10 sensorAHT10;  //Da um "apelido" para a biblioteca do sensor

//-------------------------------------------------INICIA O SENSOR----------------------------------------------------------------------------//

//SENSOR
void iniciaSensor() {
  //Se a inicialização do sensor der verdadeiro, avisa que foi encontrado,
  //caso contrário pede para verificar o circuito
  if (sensorAHT10.begin()) {
    Serial.println("AHT10 encontrado");
  } else {
    Serial.println("AHT10 não foi encontrado, verifique o circuito");
    while (1) 
    delay(100);
  }
}

//-------------------------------------------------LED RGB----------------------------------------------------------------------------//

void apontaErro(float temp, float humidity) {
  //Se a temperatura estiver abaixo de 26,6°C ou acima de 36,0°C o led RGB acende na cor vermelha
  //Se a umidade relativa do ar estiver abaixo de 29,75% ou acima de 66,50% o led RGB acende na cor amarela
  //Se tudo estiver nas condições corretas o led acende na cor branca
  if (temp <= 26.6 || temp >= 36) {
    analogWrite(ledVermelho, 0);
    analogWrite(ledVerde, 255);
    analogWrite(ledAzul, 255);
  } else if (humidity <= 29.75 || humidity >= 66.5) {
    Serial.print("umidade");
    analogWrite(ledVermelho, 0);
    analogWrite(ledVerde, 0);
    analogWrite(ledAzul, 255);
  } else {
    analogWrite(ledVermelho, 0);
    analogWrite(ledVerde, 0);
    analogWrite(ledAzul, 0);
  }
}

//-------------------------------------------------SETUP E LOOP----------------------------------------------------------------------------//

//SETUP
void setup() {
  Serial.begin(115200);        //inicia o serial na velocidade 115200
  Wire.begin(sdaPin, sclPin);  //inicia o display nas portas SDA e SCL
  lcd.init();                  //inicia o display lcd
  lcd.backlight();             ///liga a luz do display
  iniciaSensor(); //inicia o funcionamento do sensor AHT10
}

//float temp = pegaTemperatura();  //coleta o valor da temperatura por meio do AHT10
//float umid = pegaUmidade();  

void loop() {
  sensors_event_t humidity, temp;          //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  sensorAHT10.getEvent(&humidity, &temp);

  //DISPLAY
  lcd.setCursor(0, 0);
  lcd.print("Temp.:");
  lcd.print(temp.temperature);
  lcd.print(" ");
  lcd.print(char(42));
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Umidade:");
  lcd.print(humidity.relative_humidity);
  lcd.print(" %");

  apontaErro(temp.temperature, humidity.relative_humidity);

  alimentarBanco(humidity.relative_humidity, temp.temperature, "10:01", 1);

  delay(5000);
}
