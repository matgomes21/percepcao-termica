char input;
 
void setup() {
    Serial.begin(9600); 
 
    Serial.println("Type something!");
}
 
void loop() {
    Serial.read('s');
    if(Serial.available()){
        input = Serial.read();
        if(input == 's')Serial.println("ok");
        delay(500);
    }
    delay(500);
}
