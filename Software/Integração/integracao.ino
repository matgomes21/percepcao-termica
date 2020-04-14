// Including libraries
#include "U8glib.h"
#include <Wire.h>
#include "Protocentral_MAX30205.h"
#include <x9c10x.h>
#include <Buzzer.h>
#include <PushButton.h>
#include <LedRGB.h>

// Defining pins
#define btnTeste 2
#define btnControl1 3
#define btnControl2 4
#define pin1RGB 5 // Green pin
#define pin2RGB 6 // Blue pin
#define pin3RGB 7 // Red pin
#define UD 8
#define INC 9
#define CS 10
#define buzzer 11

// Creating objects
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
MAX30205 tempSensor;
x9c10x pot(CS, INC, UD);
Buzzer buz(buzzer);
PushButton btnT(btnTeste);
PushButton btnC1(btnControl1);
PushButton btnC2(btnControl1);
LedRGB rgb(pin1RGB, pin2RGB, pin3RGB);

// Creating variables
boolean a = LOW,
        savepressed = 0x01;
int menu = 1;
float   temperatura,
        c = 0,
        t1 = 0,
        t2 = 0,
        t3 = 0,
        temp_limiar = 0;

unsigned long previousMillis = 0;
const long interval = 2000;

// Collects and updates the temperature of the sensor max30205
void update_max()
{
    if (currentMillis - previousMillis >= interval)
    {
        temperatura = tempSensor.getTemperature();
        previousMillis = currentMillis;
    }
}

// Struct with screen methods
typedef struct oled
{
    void menuInit()
    {
        // Turn on green light on LED
        rgb.turnOn('g');

        // Header
        u8g.setFont(u8g_font_8x13B);
        u8g.drawRBox(0, 0, 127, 16, 2);
        u8g.setColorIndex(0);
        u8g.drawStr(17, 13, "Menu Inicial");
        u8g.setColorIndex(1);

        // Body
        u8g.setFont(u8g_font_8x13); //Determina tamanho da fonte
        u8g.drawStr(5, 30, "1.Temp Corporal");
        u8g.drawStr(5, 45, "2.Iniciar Teste");
    };

    void menuTC()
    {
        // Turns on Blue light on led
        rgb.turnOn('b');

        // Header
        u8g.setFont(u8g_font_8x13B);
        u8g.drawRBox(0, 0, 127, 16, 2);
        u8g.setColorIndex(0);
        u8g.drawStr(14, 13, "TEMP CORPORAL");
        u8g.setColorIndex(1);

        // Body
        // Temperature Square
        u8g.drawRFrame(0, 17, 88, 46, 2);
        u8g.setFont(u8g_font_fub20);

        // Updates displayed temperature
        u8g.setPrintPos(6, 50);
        u8g.print(temperatura, 1);
        // Draw "ºC"
        u8g.drawCircle(62, 33, 3);
        u8g.drawStr(66, 50, "C");
    }

    void menuTest()
    {
        void update_max();

        if (temp_limiar == 0)
        {
            // Header
            u8g.setFont(u8g_font_8x13B);
            u8g.drawRBox(0, 0, 127, 16, 2);
            u8g.setColorIndex(0);
            u8g.drawStr(14, 13, "TEMP CORPORAL");
            u8g.setColorIndex(1);

            // Body
            // Temperature Square
            u8g.drawRFrame(0, 17, 88, 46, 2);
            u8g.setFont(u8g_font_fub20);

            //Updates displayed temperature
            u8g.setPrintPos(6, 50);
            u8g.print(temperatura, 1);
            //Draw "ºC"
            u8g.drawCircle(62, 33, 3);
            u8g.drawStr(66, 50, "C");

            if (t1 != 0)
            {
                // Header t1
                u8g.drawRFrame(87, 16, 40, 15, 2);
                u8g.setFont(u8g_font_6x12);
                // Updates on display value of t1
                u8g.setPrintPos(92, 26);
                u8g.print(t1, 1);
                u8g.drawCircle(117, 19, 1);
                u8g.drawStr(119, 26, "C");
                u8g.setColorIndex(1);
            }

            if (t2 != 0)
            {
                // Header t2
                u8g.drawRFrame(87, 31, 40, 15, 2);
                u8g.setFont(u8g_font_6x12);
                // Updates on display value of t2
                u8g.setPrintPos(92, 42);
                u8g.print(t2, 1);
                u8g.drawCircle(117, 35, 1);
                u8g.drawStr(119, 42, "C");
                u8g.setColorIndex(1);
            }
            if (t3 != 0)
            {
                // Header t3
                u8g.drawRFrame(87, 46, 40, 15, 2);
                u8g.setFont(u8g_font_6x12);
                // Updates on display value of t3
                u8g.setPrintPos(92, 56);
                u8g.print(t3, 1);
                u8g.drawCircle(117, 48, 1);
                u8g.drawStr(119, 56, "C");
                u8g.setColorIndex(1);
            }
        }
        if (temp_limiar != 0)
        {
            // Header
            u8g.setFont(u8g_font_8x13B);
            u8g.drawRBox(0, 0, 127, 16, 2);
            u8g.setColorIndex(0);
            u8g.drawStr(17, 13, "TEMP LIMIAR");
            u8g.setColorIndex(1);

            // Body
            // Temperature Square
            u8g.drawRFrame(23, 17, 93, 46, 2);
            u8g.setFont(u8g_font_fub20);
            // Updates displayed temperature
            u8g.setPrintPos(30, 50);
            u8g.print(temp_limiar, 1);
            // Draw "ºC"
            u8g.drawCircle(88, 33, 3);
            u8g.drawStr(92, 50, "C");
        }
    }

} Screen;

Screen screen;

// Executes the threshold test of the collected temperatures
void testLimiar()
{
    if (button.isPressed())
    {

        if (c != 3)
        {
            buz.beep(500);
            int counter = 0;
            bool y = true;
            boolean flag = LOW;

            if (flag == LOW)
            {
                rgb.turnOn('r');
                while (y)
                {
                    pot.upOnce(1, 500);
                    screen.menuTest();

                    if (button.isPressed())
                    {
                        y = false;
                        stopPrint(c);
                    }
                    counter++;
                }
            }
            flag = !flag;

            if (flag == HIGH)
            {
                // Turn on blue light
                rgb.turnOn('b');
                for (int i = 1; i <= counter; i++)
                {
                    pot.downOnce(1, 500);
                    screen.menuTest();
                }
            }
        }

        if (c == 3)
        {
            temp_limiar = (t1 + t2 + t3) / 3;
            c = 0;
            delay(2000);
        }
    }
    rgb.turnOn('w');
    screen.Test();

}

// Executes the screens transitions
void changeMenu()
{
    if (btnC1.pressed() && !savepressed)
    {
        menu = 2;
        savepressed = 0x01;
        delay(200);
    }
    else if (btnC1.pressed() && savepressed)
    {
        menu = 1;
        savepressed = 0x00;
        delay(200);
    }
    if (btnC2.pressed() && !savepressed)
    {
        menu = 3;
        savepressed = 0x01;
        delay(200);
    }
    if (btnC2.pressed() && savepressed)
    {
        menu = 1;
        savepressed = 0x00;
        delay(200);
    }
    chooseMenu();
}

void chooseMenu()
{
    switch (menu)
    {
    // Initial Menu
    case 1:
        screen.menuInit();
        break;
    
    // Actual Temperature Menu
    case 2:
        screen.menuTC();
        break;

    // Testing Menu
    case 3:
        screen.menuTest();
        testLimiar();
        break;
    }
}

void setup()
{
    // Initialization of comunication
    Serial.begin(9600);
    tempSensor.begin();
    Wire.begin();
    Serial.begin(9600);

    // Set button
    button.interrupt();

    // Set Pot Digital
    pot.set(0, 100);
}

void loop()
{
    // Upadate Screens
    u8g.firstPage();
    do
    {
        changeMenu();
    } while (u8g.nextPage());

    delay(50);
}