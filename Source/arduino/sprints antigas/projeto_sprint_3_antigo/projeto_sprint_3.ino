//Importação de arquivos com função de o que cada componente deve fazer
#include <Wire.h>               //Gerencia a comunicação entre os dispositivos através do protocolo I2C
#include <Adafruit_AHT10.h>     //Sensor AHT10
#include <LiquidCrystal_I2C.h>  //Display lcd
#include <string>               //inclui o tipo de variável string

Adafruit_AHT10 sensorAHT10;  //Da um "apelido" para a bilbioteca do sensor

//Variaveis para as portas
const int ledVermelho = 40;
const int ledVerde = 38;
const int ledAzul = 37;

#define sdaPin 4
#define sclPin 6

float tempValor = 0;
float umidValor = 0;

int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

//SENSOR
void iniciaSensor() {
  //Wire.begin(sdaPin, sclPin); //inicia o sensor nas portas SDA e SCL

  //Se a inicialização do sensor der verdadeiro, avisa que foi encontrado,
  //caso contrário pede para verificar o circuito
  if (sensorAHT10.begin()) {
    Serial.println("AHT10 encontrado");
  } else {
    Serial.println("AHT10 não foi encontrado, verifique o circuito");
    while (1) delay(10);
  }
}

float pegaTemperatura() {
  sensors_event_t umid, temp;          //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  sensorAHT10.getEvent(&umid, &temp);  //O sensor AHT10 oleta os valores de umidade e temperatura

  return temp.temperature;  //retorna o valor da temperatura
}

float pegaUmidade() {
  sensors_event_t umid, temp;          //Declara as variaveis onde serão guardados os valores de umidade e temperatura
  sensorAHT10.getEvent(&umid, &temp);  //O sensor AHT10 oleta os valores de umidade e temperatura

  return umid.relative_humidity;  //retorna o valor da umidade
}

//LED RGB
void apontaErro(float temp, float umid) {
  //Se a temperatura estiver abaixo de 26,6°C ou acima de 36,0°C o led RGB acende na cor vermelha
  //Se a umidade relativa do ar estiver abaixo de 29,75% ou acima de 66,50% o led RGB acende na cor amarela
  //Se tudo estiver nas condições corretas o led acende na cor branca
  if (temp <= 26.6 || temp >= 36) {
    analogWrite(ledVermelho, 0);
    analogWrite(ledVerde, 255);
    analogWrite(ledAzul, 255);
  } else if (umid <= 29.75 || umid >= 66.5) {
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

//DISPLAY

/*
void iniciaDisplay(){
  lcd.init(); //inicia o display lcd
  lcd.backlight(); ///liga a luz do display
}

int mostraLcd(float temp, float umid){
  //Define onde e o que vai ser escrito a respeito da temperatura no display lcd
  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.print("Temp: "); lcd.print(temp); lcd.print((char)223); lcd.print("C");
  delay(1000);

  //Define onde e o que vai ser escrito a respeito da umidade no display lcd
  lcd.setCursor(0,1);
  lcd.print(umid);
  lcd.print("Umidade: "); lcd.print(umid); lcd.println("% rH");
  delay(1000);

  //Limpa tudo
  lcd.clear();
  delay(1000);
}
*/


//SETUP
void setup() {
  Wire.begin(sdaPin, sclPin);  //inicia o display nas portas SDA e SCL
  lcd.init();                  //inicia o display lcd
  lcd.backlight();             ///liga a luz do display
  Serial.begin(115200);        //inicia o serial na velocidade 115200
  //iniciaSensor(); //inicia o funcionamento do sensor AHT10
  //iniciaDisplay(); //inicia o funcionamento do display LCD

  //iniciaWifi();//inicia o funcionamento do Wifi
}

void loop() {
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Hello, World!");
  delay(1000);

  float temp = pegaTemperatura();  //coleta o valor da temperatura por meio do AHT10
  float umid = pegaUmidade();
  //coleta o valor da umidade por meio do AHT10

  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.println("ºC");
  Serial.print("Umidade: ");
  Serial.println(umid);
  Serial.println("%");

  float horario = 10.5;
  int estufa = 8;

  //Define como serão as mensagens printadas no display
  String mensagemTemp = "Temp: " + String(temp) + " " + (char)233 + "C";
  String mensagemUmid = "Umidade: " + String(umid) + " " + "%";

  // set cursor to first column, first row

  // clears the display to print new message
  //mostraLcd(temp, umid);//Printa no display
  apontaErro(temp, umid);  //Acende o led RGB
  //char* horario = iniciaHorario();
  //alimentarBanco(umid, temp, horario, estufa);
  delay(1000);
}