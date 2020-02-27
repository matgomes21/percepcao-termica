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
    
   if(a == 1 | a == 0){
      value[count] = a;
      digitalWrite(pos[count], value[count]);
      count++;
      
      Serial.print("Saída D/A:"); 
      for(int ct=9; ct>=0; ct--) Serial.print(value[ct], BIN);
      Serial.println(" ");   
   }
  else if (a == 2) // reset
  {
    for (int c = 2; c < 12; c++) {
      digitalWrite(c, LOW);
      value[c-2] = 0;
      count = 0;
    }
    for(int ct=9; ct>=0; ct--) Serial.print(value[ct], BIN);
    Serial.println(" "); 
  
  }
  }
  if(count >= 12)
  {
    for (int c = 2; c < 12; c++) {
      digitalWrite(c, LOW);
      value[c-2] = 0;
    }
    count = 0;
    for(int ct=9; ct>=0; ct--) Serial.print(value[ct], BIN);
    Serial.println(" "); 
  }
}
