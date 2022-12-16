#include <WiFi.h> //Conexão wifi
#include <HTTPClient.h> // Requisições Http
#include "config_wifi.h" //Importa biblioteca local com o nome do wifi e informações do número do canal e API KEY do ThingSpeak
#include "ThingSpeak.h" // Importa a biblioteca do thingspeak com funcionalidades 

char ssid[] = SECRET_SSID; // Nome da rede wi-fi
char pass[] = SECRET_PASS; //Senha da rede wi-fi
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

bool iniciaWifi () {

// Conecta ao wifi 
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    WiFi.begin(ssid, pass);  
    Serial.print(".");
    delay(5000);

    return false;    
  } else {
    Serial.println("\nConnected.");
  }

  
  while (!Serial) {
    ; // Indica conexão com a porta do serial
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Inicia ThingSpeak

  return true;
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

