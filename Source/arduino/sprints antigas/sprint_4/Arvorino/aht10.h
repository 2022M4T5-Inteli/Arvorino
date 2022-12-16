#include <Wire.h>               //Gerencia a comunicação entre os dispositivos através do protocolo I2C
#include <Adafruit_AHTX0.h>     //Sensor AHT10
Adafruit_AHTX0 aht;             //Da um "apelido" para a biblioteca do sensor


void iniciaSensor() {

  //Se a inicialização do sensor der verdadeiro, avisa que foi encontrado,
  //caso contrário pede para verificar o circuito
  if (!aht.begin(&Wire, 0x38)) {
    Serial.println("AHT10 não foi encontrado, verifique o circuito");
    while (1) delay(10);
  } else {
    Serial.println("AHT10 encontrado");
  }
}

float pegaTemperatura(){
  sensors_event_t humidity, temp; //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  aht.getEvent(&humidity, &temp); //coleta os dados de temperatura e umidade

  return temp.temperature; //retorna apenas o dado de temperatura
}

float pegaUmidade(){
  sensors_event_t humidity, temp; //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  aht.getEvent(&humidity, &temp); //coleta os dados de temperatura e umidade

  return humidity.relative_humidity; //retorna apenas o dado de umidade
}