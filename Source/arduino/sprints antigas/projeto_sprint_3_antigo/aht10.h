#include <Wire.h> //Gerencia a comunicação entre os dispositivos através do protocolo I2C
#include <Adafruit_AHT10.h> //Sensor AHT10
Adafruit_AHT10 sensorAHT10; //Da um "apelido" para a bilbioteca do sensor

//Variaveis que armazenam o numero das portas
// const int sdaPin = 10;
// const int sclPin = 8;

//Declara a variavel que armazena os valores de temperatura e umidade
float tempValor = 0;
float umidValor = 0;

void iniciaSensor(){
  Wire.begin(sdaPin, sclPin); //inicia o sensor nas portas SDA e SCL

  //Se a inicialização do sensor der verdadeiro, avisa que foi encontrado,
  //caso contrário pede para verificar o circuito
  if (sensorAHT10.begin()) {
    Serial.println("AHT10 encontrado");
  } else {
    Serial.println("AHT10 não foi encontrado, verifique o circuito");
    while (1) delay(10);
  }
}

float pegaTemperatura(){
  sensors_event_t umid, temp; //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  sensorAHT10.getEvent(&umid, &temp); //O sensor AHT10 oleta os valores de umidade e temperatura

  return temp.temperature; //retorna o valor da temperatura
}

float pegaUmidade(){
  sensors_event_t umid, temp; //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  sensorAHT10.getEvent(&umid, &temp); //O sensor AHT10 oleta os valores de umidade e temperatura

  return temp.temperature; //retorna o valor da umidade
}
