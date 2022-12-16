#include <Wire.h>               //Gerencia a comunicação entre os dispositivos através do protocolo I2C
#include <Adafruit_AHT10.h>     //Sensor AHT10
Adafruit_AHT10 sensorAHT10;     //Da um "apelido" para a biblioteca do sensor

#define sdaPin 45 //define a porta referente ao pino sda
#define sclPin 47 //define a porta referente ao pino scl

void iniciaSensor() {
  Wire.begin(sdaPin, sclPin);  //inicia o display nas portas SDA e SCL

  //Se a inicialização do sensor der verdadeiro, avisa que foi encontrado,
  //caso contrário pede para verificar o circuito
  if (sensorAHT10.begin()) {
    Serial.println("AHT10 encontrado");
  } else {
    Serial.println("AHT10 não foi encontrado, verifique o circuito");
    while (1) 
    delay(10);
  }
}

float pegaTemperatura(){
  sensors_event_t humidity, temp; //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  sensorAHT10.getEvent(&humidity, &temp); //coleta os dados de temperatura e umidade

  return temp.temperature; //retorna apenas o dado de temperatura
}

float pegaUmidade(){
  sensors_event_t humidity, temp; //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  sensorAHT10.getEvent(&humidity, &temp); //coleta os dados de temperatura e umidade

  return humidity.relative_humidity; //retorna apenas o dado de umidade
}