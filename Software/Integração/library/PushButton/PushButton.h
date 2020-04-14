/*
 * Blioteca para acionamento do buzzer
 * Matheus Gois Vieira
 * Abril de 2020
*/

#ifndef PUSHBUTTON_H_INCLUDE
#define PUSHBUTTON_INCLUDE

#include <Arduino.h>

class PushButton
{
private:
    int _pin;

public:
    PushButton(int pin);
    boolean pressed(void);
    boolean isPressed(void);
    void interrupt(void);
};

#endif
