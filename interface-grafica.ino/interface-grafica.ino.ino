//github.com/olikraus/u8glib/wiki/userreference
#include "U8glib.h"
#include <string.h>

//--- integração com o led e buzzer ---
#define PUSH_BUTTON_PIN 2 // O botão está conectado no pino digital 2 do arduino
#define RED_LED_PIN 8 // O led vermelho está conectado no pino digital 8 do arduino
#define GREEN_LED_PIN 9 // O led verde está conectado no pino digital 9 do arduino
#define BLUE_LED_PIN 10 // O led azul está conectado no pino digital 10 do arduino
#define BUZZER_PIN 11 // O buzzer está conectado no pino digital 11 do arduino (Nesse caso é um led branco, mas funciona da mesma forma)
// -----------------------------------------------------

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
// devices with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device
 
//U8GLIB_ST7920_192X32_4X u8g(10);      // SPI Com: SCK = en = 13, MOSI = rw = 11, CS = di = 10, HW SPI
//U8GLIB_ST7920_202X32_1X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_202X32_4X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_202X32_1X u8g(18, 16, 17);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9); // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);     // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_PCF8812 u8g(13, 11, 10, 9, 8);     // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_ILI9325D_320x240 u8g(18,17,19,U8G_PIN_NONE,16 );           // 8Bit Com: D0..D7: 0,1,2,3,4,5,6,7 en=wr=18, cs=17, rs=19, rd=U8G_PIN_NONE, reset = 16
//U8GLIB_SBN1661_122X32 u8g(8,9,10,11,4,5,6,7,14,15, 17, U8G_PIN_NONE, 16);     // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 cs1=14, cs2=15,di=17,rw=16,reset = 16
//U8GLIB_SSD1306_128X64 u8g(10, 9);     // HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST); // Fast I2C / TWI 
//U8GLIB_SSD1306_128X64_2X u8g(U8G_I2C_OPT_NONE);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC
 
#define b1 2
#define b2 3
#define acenador 4

 
void setup(void) 
{
  // Define os leds como saída. Ou seja, seu valor será definido dentro do código, que será passado para o arduino e ligará/desligará o led de acordo com o funcionamento do sistema.
  pinMode(RED_LED_PIN, OUTPUT);    
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED_PIN, 1); // led verde é ligado (write = escreve/define o valor de saída - 5V (1) ou 0V(0)), indicando que o sistema está funcionando.

  
  Serial.begin(9600);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  pinMode(b1,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);
  pinMode(acenador,INPUT_PULLUP);
}
 
void loop(void) 
{
  u8g.firstPage();  
  do
  {
     changeMenu();
  } while( u8g.nextPage() );
   
  delay(50);
}
