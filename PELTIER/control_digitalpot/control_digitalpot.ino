// Valores do Potenciometro
#define POT_VALUE 10000L        // Nominal POT value
#define STEP_OHMS POT_VALUE/99  // Number of ohms per tap point
#define PULSE_TIMED 10          // millisecond delay 

// Variáveis
const int pinUD = 8;            // --> X9C103P pin 2
const int pinINC = 9;           // --> X9C103P pin 1
const int CS = 10;              // --> X9C103P pin 7
const int pinWiper = A1;        // --> X9C103P pin 5
const int tapPoints = 100;     // X9C103P specs

void setup() {
  // Definindo Entradas e Saída
  pinMode (CS, OUTPUT);
  pinMode (pinUD, OUTPUT);
  pinMode (pinINC, OUTPUT);

  // Iniciando Pinos
  digitalWrite(CS, HIGH);

  // Iniciando serial
  Serial.begin(9600);
  Serial.println("Testando o Potenciometro Digital");
  


}

void X9C103P_INC(int enable, int pulse){

  digitalWrite(pulse, HIGH);   // HIGH before falling edge
                               // Not recommended for puksed key to be low 
                               // when chip select (enable) pulled low.
  delay(PULSE_TIMED);          // wait for IC/stray capacitance ?
  digitalWrite(enable,LOW);    // select the POT
  digitalWrite(pulse, LOW);    // LOW for effective falling edge
  delay(PULSE_TIMED);          // wait for IC/stray capacitance ?
                               // tap point copied into non-volatile memory
                               // if CS returns HIGH while INC is HIGH
  digitalWrite(enable,HIGH);   //deselect the POT 

}

void loop() {
  if (Serial.available() > 0) {
    char value = Serial.read();
    if (value == 'z') {
      // Move the tap point one count
      digitalWrite(pinUD, true);
      X9C103P_INC(CS, pinINC);
      delay(200);     // delay a bit for viewing
      Serial.println("inc");
    }if(value == 'x'){
      digitalWrite(pinUD, false);
      X9C103P_INC(CS, pinINC);
      delay(200);     // delay a bit for viewing
      Serial.println("dec");
    }
  }
  Serial.print(".");
  delay(1000);

}
