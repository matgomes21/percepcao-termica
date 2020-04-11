#include <ezButton.h>

#define led 5
#define bt 4
ezButton button(bt);
boolean x = LOW;
static unsigned long delayEstado;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, x);
}

void loop() {
  button.loop();
  if (button.isPressed()) {
    button.debaunce(100);
    digitalWrite(led, x);
    x = !x;
  }
  
}
