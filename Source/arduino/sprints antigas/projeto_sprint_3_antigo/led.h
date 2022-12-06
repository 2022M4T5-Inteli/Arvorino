//Variaveis para as portas
const int ledVermelho = 37;
const int ledVerde = 38;
const int ledAzul = 39;

void apontaErro(float temp, float umid){
  //Se a temperatura estiver abaixo de 26,6°C ou acima de 36,0°C o led RGB acende na cor vermelha
  //Se a umidade relativa do ar estiver abaixo de 29,75% ou acima de 66,50% o led RGB acende na cor amarela
  //Se tudo estiver nas condições corretas o led acende na cor branca
  if(temp <= 26.6  || temp >= 36 ){
    analogWrite(ledVermelho, 0);
    analogWrite(ledVerde, 255);
    analogWrite(ledAzul, 255);
  }else if(umid<= 29.75 || umid >= 66.5){
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
