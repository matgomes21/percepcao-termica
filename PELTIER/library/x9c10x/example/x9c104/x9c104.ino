#include <x9c10x.h>

x9c10x pot(10,9,8);
 
void setup() {
    Serial.begin(9600); 
    pot.set(0,10);
}
 
void loop() {
    if(Serial.available()>0){
      char c = Serial.read();
      if(c == 'u')pot.up(1,1000);
      if(c == 'd')pot.down(1,1000);      
    }    
}
