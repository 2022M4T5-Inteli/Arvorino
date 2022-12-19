#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  //Display lcd

#define sdaPin 45
#define sclPin 47

int lcdColumns = 16; //declara o numero de colunas do display
int lcdRows = 2; //declara o numero de linhas do display
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); //define o tamanho do display

void iniciaDisplay(){
  Wire.begin(sdaPin, sclPin); //inicia o display nas portas SDA e SCL
  lcd.init(); //inicia o display lcd
  lcd.backlight(); //liga a luz do display

  lcd.setCursor(4, 0);
  lcd.print("ARVORINO");
}

void printaTempUmid(float temperatura, float umidade){
  
  //Printa as informações da primeira linha (dados referentes à temperatura)
  lcd.setCursor(0, 0);
  lcd.print("Temp.:");
  lcd.print(temperatura);
  lcd.print(" ");
  lcd.print(char(42));
  lcd.print("C");

  //Printa as informações da segunda linha (dados referentes à umidade)
  lcd.setCursor(0, 1);
  lcd.print("Umidade:");
  lcd.print(umidade);
  lcd.print(" %");
}

void printaErro(){
  lcd.setCursor(1,0);
  lcd.print("Cheque o WiFi");

  lcd.setCursor(3,1);
  lcd.print("ou energia");
}