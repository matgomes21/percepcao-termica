// Incluindo Bibliotecas
#include "U8glib.h"
#include <Wire.h>
#include "Protocentral_MAX30205.h"
#include <x9c10x.h>
#include <Buzzer.h>
#include <PushButton.h>

// Create definition
#define led 5
#define bt 2
#define buz 7

// Create objects
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
MAX30205 tempSensor;
x9c10x pot(10, 9, 8);
Buzzer buzz(buz);
PushButton button(bt);


boolean a = LOW;
float temperatura;
float c = 0;
float t1 = 0, t2 = 0, t3 = 0, temp_limiar = 0;

unsigned long previousMillis = 0;
//Intervalo de medicao temperatura
const long interval = 2000;

void draw()
{
  if (temp_limiar == 0) {
    //Retangulo temperatura atual
    u8g.drawRFrame(0, 17, 88, 46, 2);
    u8g.setFont(u8g_font_fub20);
    //Atualiza a temperatura no display
    u8g.setPrintPos(6, 50);
    u8g.print(temperatura,1);
    //Circulo grau
    u8g.drawCircle(62, 33, 3);
    u8g.drawStr( 66, 50, "C");

    //Box superior amarelo
    u8g.setFont(u8g_font_8x13B);
    u8g.drawRBox(0, 0, 127, 16, 2);
    u8g.setColorIndex(0);
    u8g.drawStr( 14, 13, "TEMP CORPORAL");
    u8g.setColorIndex(1);

    if (t1 != 0) {
      //box t1
      u8g.drawRFrame(87, 16, 40, 15, 2);
      u8g.setFont(u8g_font_6x12);
      //Atualiza na tela o valor da t1
      u8g.setPrintPos(92, 26);
      u8g.print(t1,1);
      u8g.drawCircle(117, 19, 1);
      u8g.drawStr(119, 26, "C");
      u8g.setColorIndex(1);
    }

    if (t2 != 0) {
      //box t2
      u8g.drawRFrame(87, 31, 40, 15, 2);
      u8g.setFont(u8g_font_6x12);
      //Atualiza na tela o valor da t1
      u8g.setPrintPos(92, 42);
      u8g.print(t2,1);
      u8g.drawCircle(117, 35, 1);
      u8g.drawStr(119, 42, "C");
      u8g.setColorIndex(1);
    }
    if (t3 != 0) {
      //box t3
      u8g.drawRFrame(87, 46, 40, 15, 2);
      u8g.setFont(u8g_font_6x12);
      //Atualiza na tela o valor da t1
      u8g.setPrintPos(92, 56);
      u8g.print(t3,1);
      u8g.drawCircle(117, 48, 1);
      u8g.drawStr(119, 56, "C");
      u8g.setColorIndex(1);
    }
  }
  if (temp_limiar != 0) {
    //Retangulo temperatura atual
    u8g.drawRFrame(23, 17, 93, 46, 2);
    u8g.setFont(u8g_font_fub20);
    //Atualiza a temperatura no display
    u8g.setPrintPos(30, 50);
    u8g.print(temp_limiar,1);
    //Circulo grau
    u8g.drawCircle(88, 33, 3);
    u8g.drawStr( 92, 50, "C");

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
      c++;
  }
}

void setup(void)
{
  // initialization of comunication
  Serial.begin(9600);
  tempSensor.begin();
  Wire.begin();
  Serial.begin(9600);

  // Initialization of led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // Set Buzzer
  pinMode(7, OUTPUT);

  //Set button
  button.interrupt();

  // Initialization monitor serial
  Serial.println("Iniciando Controle do Pontenciometro... \n");
  pot.set(0, 100);
}

void loop(void)
{
  
  if (button.isPressed()) {   

    if (c != 3) {
      buzz.beep(500);
      int counter = 0;
      bool y = true;
      boolean flag = LOW;

      if (flag == LOW) {
        digitalWrite(led, HIGH);
        while (y) {
          pot.upOnce(1, 500);
          updateOled();

          if (button.isPressed()) {
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
