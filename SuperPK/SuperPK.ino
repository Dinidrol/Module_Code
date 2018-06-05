
byte LATCH = 12;

byte HALL[]={2,3,4,5};

byte BOOM[]=(A0, A1);

byte EARS[]={6,7,8,9,10};

bool Stage = false;
bool BOOM = false;

void setup() {
  Serial.begin(9600);
  
  for(int i = 0; i<5; i++){
    pinMode(HALL[i],INPUT);
  }
  
  pinMode(LATCH, OUTPUT);
   digitalWrite(LATCH, LOW);
}

void loop() {
  msg = serial();
  
  if(msg == "40"){
    if(Stage == false){
      
      digitalWrite(LATCH, HIGH);
      Serial.print("OFF");
      delay(100);
      digitalWrite(LATCH, LOW);
      msg = "";
    }
    else if(Stage == true){
      digitalWrite(LATCH, HIGH);
      Serial.print("ON");
      delay(100);
      digitalWrite(LATCH, LOW);
      msg = "";
    }
  }

  if(msg == "41"){
    Stage = true;    
    msg = "";
  }
  
  if (digitalRead(HALL[0]) == LOW && digitalRead(HALL[1]) == LOW && digitalRead(HALL[2]) == LOW && digitalRead(HALL[3]) == LOW && Stage == false){
    Stage = true;
  }
}

String serial(){
 if (Serial.available() > 0) {
       String c = Serial.readString(); 
       Serial.flush();
       return c;
 }
 return "0";
}
