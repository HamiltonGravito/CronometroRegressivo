#include "displayLCD.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

  //Variavél recebe tempo de jogo;
  int tempoEscolhido = 60;
  //Recebe tempo total de jogo em minutos menos o segundo inicial;
  int tempoFormatado = tempoEscolhido - 1;
  //Recebe horas de jogo;
  int horas;
  //Recebe minutos de jogo;
  int minutos;
  //Recebe segundos de jogo;
  int segundos;
  
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);

  //Configuração Inicial do Cronômetro;
  horas = tempoFormatado / 60;
  Serial.print("Hora Inicial: ");
  Serial.println(horas);
  minutos = tempoFormatado % 60;
  Serial.print("Minuto Inicial: ");
  Serial.println(minutos);
  segundos = 60;
  Serial.print("Segundo Inicial: ");
  Serial.println(segundos);
  //Fim da configuração do cronômetro;
}

void loop() {
  cronometro(tempoFormatado);
}

//Função que inicia a contagem, recebe o tempoFormatado; 
void cronometro(int tempoMin){

//O LOOP acontece enquanto segundos forem diferentes de zero (valor que muda dentro de condições IF ao final do laço);
  while(segundos != 0){
    Serial.println("Entrou no LAÇO");

    //Verifica se a hora é menor que 10 para formatação do texto e se não apenas escreve a hora;
    if(horas < 10){
      Serial.print("Horas LAÇO: ");
      Serial.println(horas);
      lcd.setCursor(4,1);
      lcd.print('0');
      lcd.print(horas);
    }else {
      Serial.print("Horas LAÇO: ");
      Serial.println(horas);
      lcd.setCursor(4,1);
      lcd.print(horas);
    }

    //Escreve os dois pontos do formato horas ":" ;
    lcd.setCursor(6,1);
    lcd.print(":");

    //Verifica se o minuto é menor que 10 para formatação do texto;
    if(minutos < 10){
      Serial.print("Minutos LAÇO: ");
      Serial.println(minutos);
      lcd.setCursor(7,1);
      lcd.print('0');
      lcd.print(minutos);
    //Verifica se os minutos + segundos equivalem a 1 hora se sim formata a saída, se não apenas exibe os minutos;
    }else if ((minutos == 59) && (segundos == 60)){
      int horasVisor = horas + 1;
        if(horasVisor < 10){
        lcd.setCursor(4,1);
        lcd.print('0');
        lcd.print(horasVisor);
      
        lcd.setCursor(7,1);
        lcd.print("00");
        }else {
          lcd.setCursor(4,1);
          lcd.print(horasVisor);
        }
    }else {
      Serial.print("Minutos LAÇO: ");
      Serial.println(minutos);
      lcd.setCursor(7,1);
      lcd.print(minutos);
    }

   //Escreve os dois pontos do formato  horas":"minutos":" ; 
    lcd.setCursor(9,1);
    lcd.print(":");

  //Verifica se o segundo é menor que 10 para formatação do texto;
    if(segundos < 10){
      Serial.print("Segundos LAÇO: ");
      Serial.println(segundos);
      lcd.setCursor(10,1);
      lcd.print('0');
      lcd.print(segundos);
    //Formata minutos para segundos igual a 60;
    }else if(segundos == 60){
      int minutosVisor = minutos + 1;
      if((minutos >= 0) && (minutos < 59)){
        if(minutosVisor < 10){
          lcd.setCursor(7,1);
          lcd.print('0');
          lcd.print(minutosVisor);
        }else {
          lcd.setCursor(7,1);
          lcd.print(minutosVisor);
        }
      }
      lcd.setCursor(10,1);
      lcd.print("00");
      }else {
      Serial.print("Segundos LAÇO: ");
      Serial.println(segundos);
      lcd.setCursor(10,1);
      lcd.print(segundos);
    }
    //Exibe a tela durante 1 segundo e diminui segundos;
    delay(1000);
    lcd.clear();
    segundos --;

    //
    if((horas > 0) && (segundos == 0)){
    Serial.println("Entrou no IF horas > 0");
      if(minutos != 0){
        minutos --;
        segundos = 60;
      }else {
        horas --;
        minutos = 59;
        segundos = 60;
      }
    
   }

   if((horas == 0) && (minutos != 0) && (segundos == 0)){
    Serial.println("Entrou no IF horas == 0 e minutos != 0");
    segundos = 60;
    minutos --;
   }

   if((horas > 0) && (minutos == 00) && (segundos == 0)){
    Serial.println("Entrou no IF horas > 0 e minutos == 0");
    segundos = 60;
    horas --;
   }

   if((horas == 1) && (minutos == 0) && (segundos == 0)){
    Serial.println("Entrou no Quarto IF");
    segundos = 60;
    horas --;
    minutos = 59;
   }
  
   if((horas == 0) && (minutos == 0) && (segundos == 0)){
    lcd.setCursor(2,0);
    lcd.print("GAME OVER!!!");
    delay(1000);
  }
 }
}
