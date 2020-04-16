#define led 7
void setup(){
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}
void loop(){
    digitalWrite(led, HIGH);
    Serial.println("Ligado");
    delay(2000);
    digitalWrite(led,LOW);
    Serial.println("Desligado");
    delay(2000);

}