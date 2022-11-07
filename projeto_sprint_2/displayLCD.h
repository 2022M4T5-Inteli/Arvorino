#include <Wire.h> //Gerencia a comunicação entre os dispositivos através do protocolo I2C
#include <LiquidCrystal_I2C.h> //Display lcd
#include <string> //inclui o tipo de variável string

//Variaveis que armazenam o numero das portas
const int sdaPin = 10;
const int sclPin = 8;

//Linhas e colunas do display lcd
const int lcdLinhas = 2;
const int lcdColunas = 16;

//Definição da configuração de tamanho do display
LiquidCrystal_I2C lcd(0x27, lcdColunas, lcdLinhas);

void iniciaDisplay(){
  Wire.begin(sdaPin, sclPin); //inicia o display nas portas SDA e SCL
  lcd.init(); //inicia o display lcd
  lcd.backlight(); ///liga a luz do display
}

void mostraLcd(String temp, String umid){
  //Define onde e o que vai ser escrito a respeito da temperatura no display lcd
  lcd.setCursor(0, 0);
  lcd.print(temp);
  //lcd.print("Temp: "); lcd.print(temp.temperature); lcd.print((char)223); lcd.print("C");
  delay(1000);

  //Define onde e o que vai ser escrito a respeito da umidade no display lcd
  lcd.setCursor(0,1);
  lcd.print(umid);
  //lcd.print("Umidade: "); lcd.print(umid.relative_humidity); lcd.println("% rH");
  delay(1000);

  //Limpa tudo
  lcd.clear();
  delay(1000);
}
