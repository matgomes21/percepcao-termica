/*
 * Blioteca para acionamento do buzzer
 * Matheus Gois Vieira
 * Abril de 2020
*/

#include "PushButton.h"

boolean tbut;
boolean x = LOW;

PushButton::PushButton(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

boolean PushButton::pressed()
{
    if (!digitalRead(_pin))
        tbut = 0x01;

    if (digitalRead(_pin) && tbut)
    {
        tbut = 0x00;
        delay(200);
        return true;
    }
    return false;
}
boolean PushButton::isPressed()
{
    if (x == HIGH)
    {
        x = !x;
        return true;
    }
    return false;
}
void debaunce()
{
    static unsigned long delayEstado;

    if ((millis() - delayEstado) > 100)
    {
        x = HIGH;
        delayEstado = millis();
    }
}
void PushButton::interrupt()
{
    attachInterrupt(digitalPinToInterrupt(_pin), debaunce, RISING);
}
