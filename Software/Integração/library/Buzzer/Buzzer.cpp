/*
 * Blioteca para acionamento do buzzer
 * Matheus Gois Vieira
 * Abril de 2020
*/

#include "Buzzer.h"

Buzzer::Buzzer(int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void Buzzer::beep(int temp)
{
    digitalWrite(_pin, HIGH);
    delay(temp);
    digitalWrite(_pin, LOW);
}