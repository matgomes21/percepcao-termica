#ifndef LEDRGB_H_INCLUDE
#define LEDRGB_H_INCLUDE
#include <Arduino.h>

class LedRGB
{
private:
    int green;
    int blue;
    int red;

public:
    
    LedRGB(int p1,int p2,int p3);
    void turnOn(char colour);

    
};

#endif


