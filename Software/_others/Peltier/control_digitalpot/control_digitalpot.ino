#include <Wire.h>
#include "Protocentral_MAX30205.h"
#include <x9c10x.h>

MAX30205 tempSensor;
x9c10x pot(10,9,8);

}
void setup() {

  // Iniciando i2c and serial
  Wire.begin();
  Serial.begin(9600);
  tempSensor.begin();   // set continuos mode, active mode

  Serial.println("Iniciando Controle do Pontenciometro... \n");
  pot.set(0,10);;

}

void max3025() {
  float temp = tempSensor.getTemperature(); // read temperature for every 100ms
  Serial.print(temp , 2);
  Serial.println("'c" );
  delay(100);
}

void loop() {
  max3025();
  if(Serial.available()>0){
      char c = Serial.read();
      if(c == 'u'){
        pot.up(1,1000);
        max3025();
      }
      if(c == 'd'){
        pot.down(1,1000);  
        max3025();  
      }  
    }  
  
}
