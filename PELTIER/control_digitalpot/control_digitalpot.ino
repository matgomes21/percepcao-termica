// Valores do Potenciometro
#define PULSE_TIMED       10                    // millisecond delay 
#define SERIAL_BAUD_RATE  9600                  // Baud rate to the serial


// Variáveis
const int pinUD = 8;                            // --> X9C103P pin 2
const int pinINC = 9;                           // --> X9C103P pin 1
const int CS = 10;                              // --> X9C103P pin 7
const int ohms = 10;
const int temp = 1000;

void setup() {
  // Definindo Entradas e Saída
  pinMode (CS, OUTPUT);
  pinMode (pinUD, OUTPUT);
  pinMode (pinINC, OUTPUT);

  // Iniciando Pinos
  digitalWrite(CS, HIGH);

  // Iniciando serial
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Iniciando Controle do Pontenciometro... \n");  
  
}

void X9C103P_INC() {
  // High to prepare the falling edge
  digitalWrite(pinINC, HIGH);                     // HIGH before falling edge
  delay(PULSE_TIMED);                             // wait for IC/stray capacitance
  digitalWrite(CS, LOW);                          // select the POT
  digitalWrite(pinINC, LOW);                      // LOW for effective falling edge
  delay(PULSE_TIMED);                             // wait for IC/stray capacitance
  digitalWrite(CS, HIGH);                         // standby mode
}

void loop() {
  if (Serial.available() > 0) {
    char value = Serial.read();
    switch (value) {
      case 'u':                                     // u - up
        while (1) {
          digitalWrite(pinUD, LOW);                  // With the U/D pin HIGH, the mode is Wiper UP
          for (int i = 1; i <= ohms; i++)X9C103P_INC();                              // Manage the pins state to increment
          delay(temp);                       // delay a bit for viewing
          Serial.println("Incrementando...");         // show that is incrementing
          value = Serial.read();
          if (value == 's'){
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
          Serial.println("Decrementando...");         // show that is decrementing
          value = Serial.read();
          if (value == 's'){
            Serial.println("Stop!");
            break;
          }
        }        
        break;
      default:
        Serial.println("Opção inválida.");
    }
  }
}
