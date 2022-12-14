//Importação de arquivos com função de o que cada componente deve fazer

#include <WiFi.h> //Conexão wifi
#include <HTTPClient.h> //Requisições Http
#include "ThingSpeak.h" // Importa a biblioteca do thingspeak com funcionalidades 
#include "display.h"    // Importa a biblioteca local que contém códigos sobre o funcionamento do display
#include "led.h"        // Importa biblioteca local que contém códigos sobre o funcionamento do led rgb
#include "thing_speak.h" // Importa biblioteca local que contém códigos sobre o funcionamento do ThingSpeak
#include "aht10.h" //Importa biblioteca local que contém códigos sobre o funcionanamento do aht10.h
#include "config_wifi.h" //Importa biblioteca local com credenciais do wifi e thingspeak

// Inicia os valores para as váriaveis utilizadas para os dados de temperatura e umidade
int numero1 = 10; //temperatura sensor AHT10
int numero2 = random(0,100); //umidade sensor AHT10
String myStatus = ""; 

void setup() {
  Serial.begin(115200); //Inicia o serial na velocidade 115200
  Wire.begin(45, 47); //Inicia wire do sensor do aht10 e display
  iniciaWifi(); //Inicia o funcionamento do wifi
  iniciaDisplay(); //inicia o funcionamento do display LCD
  iniciaSensor(); //inicia o funcionamento do sensor AHT10
}

void loop() {
  float temp = pegaTemperatura();
  float umid = pegaUmidade();
  
  numero1 = (int) (temp * 100); //converte o valor de temperatura para número inteiro, necessário para o thingspeak
  numero2 = (int) (umid * 100); //converte o valor de umidade para número inteiro, necessário para o thingspeak
  printaDisplay(temp, umid);
  enviaThingSpeak(numero1, numero2, myStatus);
  apontaErro(temp, umid);


}
