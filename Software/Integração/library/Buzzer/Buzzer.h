/*
 * Blioteca para acionamento do buzzer
 * Matheus Gois Vieira
 * Abril de 2020
*/

#ifndef BUZZER_H_INCLUDE
#define BUZZER_H_INCLUDE

#include <Arduino.h>

class Buzzer
{
private:
    int _pin;
public:
    Buzzer(int pin);
    void beep(int temp);
};

#endif


