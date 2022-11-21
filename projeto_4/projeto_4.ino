//Importação de arquivos com função de o que cada componente deve fazer
#include <string> //importa o tipo de variavel string
#include "led.h" //importa o arquivo referente ao led
#include "aht10.h" //importa o arquivo referente ao sensor
#include "display.h" //importa o arquivo referente ao display
#include "banco.h" //importa o arquivo referente à conexão wifi que manda os dados pro banco


void setup() {
  Serial.begin(115200); //inicia o serial na velocidade 115200
  //iniciaWifi(); //inicia o funcionamento do wifi
  iniciaDisplay(); //inicia o funcionamento do display LCD
  iniciaSensor(); //inicia o funcionamento do sensor AHT10
}

void loop() { 
  float temperatura = pegaTemperatura(); //guarda o valor da temperatura coletada pelo sensor
  float umidade = pegaUmidade(); //guarda o valor da umidade coletada pelo sensor
  String horario = "10:01"; //guarda o valor do horario
  int estufa = 1;

  printaDisplay(temperatura, umidade); //mostra no display os valores de temperatura e umidade

  apontaErro(temperatura, umidade); //acende o led com as cores baseadas nas condiçoes de funcionamento

  alimentarBanco(umidade, temperatura, horario, estufa); //manda para o banco 

  delay(5000);
}