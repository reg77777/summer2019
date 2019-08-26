int a[4]={2,3,20,19};
int b[4]={39,47,33,40};
int v[4]={37,49,31,41};
int gnd[4]={35,51,29,42};

void setup(){
    Serial.begin(9600);
    for(int i=0;i<3;i++){
       pinMode(a[i],INPUT_PULLUP); 
       pinMode(b[i],INPUT_PULLUP); 
       pinMode(v[i],OUTPUT);
       digitalWrite(v[i],HIGH);
       pinMode(gnd[i],OUTPUT);
       digitalWrite(gnd[i],LOW);
    }
}

void loop(){
    Serial.print("A");
    for(int i=0;i<3;i++){
        Serial.print(digitalRead(a[i]));
        Serial.print(" ");
    }
    Serial.print("B");
    for(int i=0;i<3;i++){
        Serial.print(digitalRead(b[i]));
        Serial.print(" ");
    }
    Serial.println();
}
