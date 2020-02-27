// Declaração de Variação
int pos[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int value[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int count = 0;
char valuestr[10];


void setup() {
  // Setando saídas
  Serial.begin(9600);
  for (int c = 2; c < 12; c++) {
    pinMode(c, OUTPUT);
  }
  Serial.println("Pode Começar!!");
}

void loop() {

 
  if (Serial.available()) {
    String b = Serial.readString();
    int a = b.toInt();
    
   
    value[count] = a;
    digitalWrite(pos[count], HIGH);
    count++;
    
    Serial.print("Saída D/A:"); 
    for(int ct=9; ct>=0; ct--) Serial.print(value[ct], BIN);
    Serial.println(" ");   
    

  }
}
