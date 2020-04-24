#include "LedRGB.h"

LedRGB::LedRGB(int p1,int p2, int p3){
    green = p1;
    blue = p2;
    red = p3;

    pinMode(green, OUTPUT);    
    pinMode(blue, OUTPUT);
    pinMode(red, OUTPUT);
}

void LedRGB::turnOn(char colour){
    switch(colour){
        case 'g':
            digitalWrite(blue,0);
            digitalWrite(green,1);
            digitalWrite(red,0);
            break;

        case 'b':
            digitalWrite(blue,1);
            digitalWrite(green,0);
            digitalWrite(red,0);
            break;

        case 'r':
            digitalWrite(blue,0);
            digitalWrite(green,0);
            digitalWrite(red,1);
            break;

        default:
            digitalWrite(blue,0);
            digitalWrite(green,0);
            digitalWrite(red,0);
            break;

    }
}

