const int ledVermelho = 40; //identifica a porta ligada na perna do led referente à cor vermelha
const int ledVerde = 38; //identifica a porta ligada na perna do led referente à cor verde
const int ledAzul = 37; //identifica a porta ligada na perna do led referente à cor azul

const int ledVermelho1 = 1; 
const int ledVerde1 =  42;
const int ledAzul1 =  41;

void apontaErroTempUmid(float temp, float humidity) {
  //Se a temperatura estiver abaixo de 26,6°C ou acima de 36,0°C o led RGB acende na cor vermelha
  //Se a umidade relativa do ar estiver abaixo de 29,75% ou acima de 66,50% o led RGB acende na cor amarela
  //Se tudo estiver nas condições corretas o led acende na cor branca
  if (temp <= 28 || temp >= 36) {
    analogWrite(ledVermelho, 0);
    analogWrite(ledVerde, 255);
    analogWrite(ledAzul, 255);
  } else if (humidity <= 70 || humidity >= 85) {
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

void acendeVermelho(){
    analogWrite(ledVermelho1, 0);
    analogWrite(ledVerde1, 255);
    analogWrite(ledAzul, 255);
  
}


void acendeVerde(){
    analogWrite(ledVermelho1, 255);
    analogWrite(ledVerde1, 0);
    analogWrite(ledAzul, 255);
  
}


/*
  SE TD DER CERTO -> ACENDE VERDE
  se nenhuma requisição for enviada, acende vermelho (led)
  printa no display: Verifique sua internet e energia
*/