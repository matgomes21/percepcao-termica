#include <Wire.h>
#include "Protocentral_MAX30205.h"
MAX30205 tempSensor;

// Valores do Potenciometro
#define PULSE_TIMED       10                    // millisecond delay 
#define SERIAL_BAUD_RATE  9600                  // Baud rate to the serial

// Variáveis
const int pinUD = 8;                            // --> X9C103P pin 2
const int pinINC = 9;                           // --> X9C103P pin 1
const int CS = 10;                              // --> X9C103P pin 7
const int ohms = 1;
const int temp = 1000;
int aux = 0;
int limit = 10;

void X9C103P_INC() {
  // High to prepare the falling edge
  digitalWrite(pinINC, HIGH);                     // HIGH before falling edge
  delay(PULSE_TIMED);                             // wait for IC/stray capacitance
  digitalWrite(CS, LOW);                          // select the POT
  digitalWrite(pinINC, LOW);                      // LOW for effective falling edge
  delay(PULSE_TIMED);                             // wait for IC/stray capacitance
  digitalWrite(CS, HIGH);                         // standby mode
}

void setar() {
  while (1) {
    digitalWrite(pinUD, HIGH);                  // With the U/D pin HIGH, the mode is Wiper UP
    for (int q = 1; q <= 100; q++)X9C103P_INC();                              // Manage the pins state to increment
    Serial.println("Pontenciometro Zerado \n");
    break;
  }
}
void setup() {
  // Definindo Entradas e Saída
  pinMode (CS, OUTPUT);
  pinMode (pinUD, OUTPUT);
  pinMode (pinINC, OUTPUT);

  // Iniciando Pinos
  digitalWrite(CS, HIGH);

  // Iniciando i2c and serial
  Wire.begin();
  Serial.begin(SERIAL_BAUD_RATE);
  tempSensor.begin();   // set continuos mode, active mode
  Serial.println("Iniciando Controle do Pontenciometro... \n");
  setar();

}


void max3025() {
  float temp = tempSensor.getTemperature(); // read temperature for every 100ms
  Serial.print(temp , 2);
  Serial.println("'c" );
  delay(100);
}

void loop() {
  //max3025();
  if (Serial.available() > 0) {
    char value = Serial.read();
    switch (value) {
      case 'u':                                     // u - up
        while (1) {
          digitalWrite(pinUD, LOW);                  // With the U/D pin HIGH, the mode is Wiper UP
          for (int k = 1; k <= ohms; k++)X9C103P_INC();                              // Manage the pins state to increment
          delay(temp);                       // delay a bit for viewing
          Serial.println("Aumentando resistencia e Diminuindo Tensão ...");                               // show that is incrementing
         
          value = Serial.read();
          aux++;
          //max3025();
          if (value == 's' or aux == limit) {
            aux = 0;
            Serial.println("Stop!");
            break;
          }
        }
        break;
      case 'd':                                     // d - down
        while (1) {
          digitalWrite(pinUD, HIGH);                   // With the U/D pin HIGH, the mode is Wiper UP
          for (int j = 1; j <= ohms; j++)X9C103P_INC();                              // Manage the pins state to decrement
          delay(temp);                       // delay a bit for viewing
          Serial.println("Diminuindo resistencia e Aumentando Tensão ...");         // show that is decrementing
          value = Serial.read();
          aux++;
          //max3025();
          if (value == 's' or aux == limit) {
            aux = 0;
            Serial.println("Stop!");
            break;
          }
        }
        break;
      default:
        Serial.println("Opção inválida.");
    }
  }
  delay(500);
}
