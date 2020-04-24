/*
 * Controle do Potenciometro Digital
 * Matheus Gois Vieira
 * Abril de 2020
*/

#ifndef X9C10X_H_INCLUDED
#define X9C10X_H_INCLUDED

#include <Arduino.h>
class x9c10x{
    public:
        x9c10x(int cs, int inc, int ud);    // Define CS, INC and U/D
        void set(int init, int lt);         // Init = initial resistance | lt = limit resistance        
        void up(int ohms, int temp);        // Speed of Ohms/Temp UP
        void down(int ohms, int temp);      // Speed of Ohms/Temp DOWN
        void downOnce(int ohms, int temp);      // Speed of Ohms/Temp DOWN
        void upOnce(int ohms, int temp);      // Speed of Ohms/Temp DOWN
        void stop(void);              // Define sudden stop button 
        void readpot(int delay_temp, String analog_pin);    // Read resistance
};

#endif