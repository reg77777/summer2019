void setup(){
    Serial.begin(9600);
    pinMode(2,INPUT);
    pinMode(3,INPUT);
}

void loop(){
    Serial.print(digitalRead(2));
    Serial.print(" ");
    Serial.print(digitalRead(3));
    Serial.println();
}
