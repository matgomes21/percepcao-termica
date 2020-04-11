#include "U8glib.h"
#include <Wire.h>
#include "Protocentral_MAX30205.h"
#include <x9c10x.h>
#include <ezButton.h>

#define led 5
#define bt 4

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

MAX30205 tempSensor;
x9c10x pot(10, 9, 8);
ezButton button(bt);

int temperatura;
int c = 0;
int t1 = 0, t2 = 0, t3 = 0, temp_limiar = 0;

unsigned long previousMillis = 0;
//Intervalo de medicao temperatura
const long interval = 2000;

void draw()
{
  if (temp_limiar == 0) {
    //Retangulo temperatura atual
    u8g.drawRFrame(0, 17, 84, 46, 2);
    u8g.setFont(u8g_font_fub20);
    //Atualiza a temperatura no display
    u8g.setPrintPos(13, 50);
    u8g.print(temperatura);
    //Circulo grau
    u8g.drawCircle(51, 33, 3);
    u8g.drawStr( 56, 50, "C");

    //Box superior amarelo
    u8g.setFont(u8g_font_8x13B);
    u8g.drawRBox(0, 0, 127, 16, 2);
    u8g.setColorIndex(0);
    u8g.drawStr( 14, 13, "TEMP CORPORAL");
    u8g.setColorIndex(1);

    if (t1 != 0) {
      //box t1
      u8g.drawRFrame(86, 16, 42, 15, 2);
      u8g.setFont(u8g_font_6x12);
      //Atualiza na tela o valor da t1
      u8g.setPrintPos(97, 26);
      u8g.print(t1);
      u8g.drawCircle(110, 19, 1);
      u8g.drawStr(112, 26, "C");
      u8g.setColorIndex(1);
    }

    if (t2 != 0) {
      //box t2
      u8g.drawRFrame(86, 31, 42, 15, 2);
      u8g.setFont(u8g_font_6x12);
      //Atualiza na tela o valor da t1
      u8g.setPrintPos(97, 42);
      u8g.print(t2);
      u8g.drawCircle(110, 35, 1);
      u8g.drawStr(112, 42, "C");
      u8g.setColorIndex(1);
    }
    if (t3 != 0) {
      //box t3
      u8g.drawRFrame(86, 46, 42, 15, 2);
      u8g.setFont(u8g_font_6x12);
      //Atualiza na tela o valor da t1
      u8g.setPrintPos(97, 56);
      u8g.print(t3);
      u8g.drawCircle(110, 48, 1);
      u8g.drawStr(112, 56, "C");
      u8g.setColorIndex(1);
    }
  }
  if (temp_limiar != 0) {
    //Retangulo temperatura atual
    u8g.drawRFrame(30, 17, 84, 46, 2);
    u8g.setFont(u8g_font_fub20);
    //Atualiza a temperatura no display
    u8g.setPrintPos(43, 50);
    u8g.print(temp_limiar);
    //Circulo grau
    u8g.drawCircle(81, 33, 3);
    u8g.drawStr( 86, 50, "C");

    //Box superior amarelo
    u8g.setFont(u8g_font_8x13B);
    u8g.drawRBox(0, 0, 127, 16, 2);
    u8g.setColorIndex(0);
    u8g.drawStr( 17, 13, "TEMP LIMIAR");
    u8g.setColorIndex(1);
  }



}

void stopPrint(int count) {
  switch (count) {
    case 0:
      t1 = temperatura;
      Serial.print("T1: ");
      Serial.print(t1);
      Serial.println("'C");
      c++;
      break;
    case 1:
      t2 = temperatura;
      Serial.print("T2: ");
      Serial.print(t2);
      Serial.println("'C");
      c++;
      break;
    default:
      t3 = temperatura;
      Serial.print("T3: ");
      Serial.print(t3);
      Serial.println("'C");
      c = 3;
  }
}

void setup(void)
{
  Serial.begin(9600);
  tempSensor.begin();
  Wire.begin();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  Serial.println("Iniciando Controle do Pontenciometro... \n");
  pot.set(0, 100);
}

void loop(void)
{
  button.loop();
  if (button.isPressed()) {
    button.debaunce(100);

    if (c != 3) {
      int counter = 0;
      bool y = true;
      boolean flag = LOW;

      if (flag == LOW) {
        digitalWrite(led, HIGH);
        while (y) {
          pot.upOnce(1, 500);
          updateOled();

          button.loop();
          if (button.isPressed()) {
            button.debaunce(100);
            y = false;
            stopPrint(c);
          }
          counter++;
        }
      }
      flag = !flag;

      if (flag == HIGH) {
        digitalWrite(led, LOW);
        for (int i = 1; i <= counter; i++) {
          pot.downOnce(1, 500);
          updateOled();
        }
      }
    }

    if(c == 3){
      temp_limiar = (t1+t2+t3)/3;
      c = 0;
      delay(2000);
    }
  }
  digitalWrite(led, LOW);
  updateOled();
}

void updateOled() {
  unsigned long currentMillis = millis();
  //Timer para ler o valor da temperatura
  if (currentMillis - previousMillis >= interval)
  {
    temperatura = tempSensor.getTemperature();
    previousMillis = currentMillis;

  }

  u8g.firstPage();
  // Chama a rotina de desenho na tela
  do
  {
    draw();
  }
  while ( u8g.nextPage() );
  delay(50);
}
