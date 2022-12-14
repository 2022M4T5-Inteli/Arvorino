#include <WiFi.h> //Conexão wifi
#include <HTTPClient.h> // Requisições Http
#include "config_wifi.h" //Importa biblioteca local com o nome do wifi e informações do número do canal e API KEY do ThingSpeak
#include "ThingSpeak.h" // Importa a biblioteca do thingspeak com funcionalidades 
#include "led.h" // Importa o arquivo local referente aos LEDs
#include "display.h" // Importa o arquivo local referente ao display

char ssid[] = SECRET_SSID; // Nome da rede wi-fi
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void iniciaWifi () {

// Conecta ao wifi 
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    acendeVermelho();
    printaErro();

    //enquanto o wifi não for conectado ele fica na espera e printando "..." no serial, assim que ele conectar ele confirma a conecção e diz o IP
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid);  
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  else{
    acendeVerde();
  }
  
  while (!Serial) {
    ; // Indica conexão com a porta do serial
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Inicia ThingSpeak
}

void enviaThingSpeak(int numero1, int numero2, String myStatus){

  // Configura os campos com as váriaveis de temperatura e umidade
  ThingSpeak.setField(1, numero1); //campo 1, temperatura
  ThingSpeak.setField(2, numero2); //campo 2, umidade
  
  // Configura o status de envio dos dados
  ThingSpeak.setStatus(myStatus);
  
  // Escreve os dados no canal do ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Canal atualizado com sucesso.");
  }
  else{
    Serial.println("Problema atualizando o canal. HTTP error code " + String(x));
  }

  delay(5000); // Espera 5 segundos para atualizar o canal do ThingSpeak
}

