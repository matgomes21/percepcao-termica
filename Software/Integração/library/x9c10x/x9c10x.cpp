/*
 * Controle do Potenciometro Digital
 * Matheus Gois Vieira
 * Abril de 2020
*/

#include "x9c10x.h"
#include <Arduino.h>
#include <ezButton.h>

#define PULSE_TIMED 10
#define cut 6
int _cs, _inc, _ud, limit, aux = 0;
char value, condicional;
int count = 0;

x9c10x::x9c10x(int cs, int inc, int ud)
{
    _cs = cs;
    _inc = inc;
    _ud = ud;
    pinMode(_cs, OUTPUT);
    pinMode(_inc, OUTPUT);
    pinMode(_ud, OUTPUT);
    digitalWrite(_cs, HIGH);
}

void x9c()
{
    // High to prepare the falling edge
    digitalWrite(_inc, HIGH); // HIGH before falling edge
    delay(PULSE_TIMED);       // wait for IC/stray capacitance
    digitalWrite(_cs, LOW);   // select the POT
    digitalWrite(_inc, LOW);  // LOW for effective falling edge
    delay(PULSE_TIMED);       // wait for IC/stray capacitance
    digitalWrite(_cs, HIGH);  // standby mode
}

void x9c10x::set(int init, int lt)
{
    int n;
    limit = lt;

    switch (init)
    {
    case 100:
        n = 0;
        break;
    case 0:
        n = 100;
        break;
    default:
        n = 50;
        break;
    }

    while (1)
    {
        if (n == 0)
            break;
        digitalWrite(_ud, HIGH);
        for (int i = 1; i <= n; i++)
            x9c();
        Serial.println("Pontenciometro Zerado \n");
        digitalWrite(cut, LOW);
        Serial.println("Tensão: 0 V \n");
        break;
    }
}

void stop()
{
    value = 's';
}

void x9c10x::readpot(int delay_temp, String analog_pin)
{
    String data = analog_pin;
    uint8_t pin = atoi(data.substring(1, 3).c_str());
    // read the input on analog pin 0:
    int sensorValue = analogRead(pin);
    // print out the value you read:
    Serial.println(sensorValue);
    delay(delay_temp); // delay in between reads for stability
}

void x9c10x::up(int ohms, int temp)
{
    while (1)
    {
        digitalWrite(cut, HIGH);
        digitalWrite(_ud, LOW);
        for (int k = 1; k <= ohms; k++)
            x9c();
        delay(temp);
        Serial.println("Aumentando Tensão ...");
        value = Serial.read();
        aux++;
        count++;
        if (value == 's' || aux == limit)
        {
            if (value == 's')
                condicional = 'c';
            aux = 0;
            Serial.println("Stop!");

            break;
        }                                                                                       
    }
}

void x9c10x::down(int ohms, int temp)
{
    while (1)
    {
        digitalWrite(cut, HIGH);
        digitalWrite(_ud, HIGH); // With the U/D pin HIGH, the mode is Wiper UP
        for (int j = 1; j <= ohms; j++)
            x9c();                               // Manage the pins state to decrement
        delay(temp);                             // delay a bit for viewing
        Serial.println("Diminuindo Tensão ..."); // show that is decrementing
        value = Serial.read();
        aux++;
        count--;
        if (value == 's' || aux == limit || (count == 0 && condicional == 'c')) {
            aux = 0;
            Serial.println("Stop!");
            break;
        }
    }
}
void x9c10x::upOnce(int ohms, int temp)
{
    digitalWrite(cut, HIGH);
    digitalWrite(_ud, LOW);
    for (int k = 1; k <= ohms; k++)
        x9c();
    delay(temp);
    Serial.println("Aumentando Tensão ...");
}

void x9c10x::downOnce(int ohms, int temp)
{
    digitalWrite(cut, HIGH);
    digitalWrite(_ud, HIGH); // With the U/D pin HIGH, the mode is Wiper UP
    for (int j = 1; j <= ohms; j++)
        x9c();                               // Manage the pins state to decrement
    delay(temp);                             // delay a bit for viewing
    Serial.println("Diminuindo Tensão ..."); // show that is decrementing
}
