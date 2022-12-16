#define ledVermelho 40 //identifica a porta ligada na perna do led referente à cor vermelha
#define ledVerde 38 //identifica a porta ligada na perna do led referente à cor verde
#define ledAzul 37 //identifica a porta ligada na perna do led referente à cor azul

#define ledRed 1
#define ledGreen 42
#define ledBlue 41


//Código referente ao 1° LED
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

//Funçoes das linhas 34 e 42, são referentes ao 2° LED

//Acende o led na cor vermelha, será chamada caso ocorra algum erro
void acendeVermelho(){
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 255);
    analogWrite(ledBlue, 255);
  
}

//Acende o led na cor verde, será chamada sempre que der tudo certo
void acendeVerde(){
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 255);
  
}


/*
  SE TD DER CERTO -> ACENDE VERDE
  se nenhuma requisição for enviada, acende vermelho (led)
  printa no display: Verifique sua internet e energia
*/