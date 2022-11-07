//Importação de arquivos com função de o que cada componente deve fazer
#include "led.h"
#include "displayLCD.h"
#include "aht10.h"

void setup(){
  Serial.begin(115200); //inicia o serial na velocidade 115200
  iniciaSensor(); //inicia o funcionamento do sensor AHT10
  iniciaDisplay(); //inicia o funcionamento do display LCD
}
void loop(){
  float temp = pegaTemperatura(); //coleta o valor da temperatura por meio do AHT10
  float umid = pegaUmidade(); //coleta o valor da umidade por meio do AHT10

  //Define como serão as mensagens printadas no display
  String mensagemTemp = "Temp: " + String(temp) + " " + (char)233 + "C";
  String mensagemUmid = "Umidade: " + String(umid) + " " + "%";
  
  mostraLcd(mensagemTemp, mensagemUmid);//Printa no display
  apontaErro(); //Acende o led RGB
}
