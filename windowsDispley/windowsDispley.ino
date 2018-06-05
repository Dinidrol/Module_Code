#define OK 3
#define LATCH 8

String msg;

byte RELE[] = {2,3,4,5};
byte MIKR[] = {6,7};
bool up1 = true;
bool dw = true;
bool opeen = false;

void setup() {
    Serial.begin(9600);
    
    pinMode(LATCH, OUTPUT);
      digitalWrite(LATCH, LOW);
   
  for(int i = 0; i<4; i++){
    pinMode(RELE[i], OUTPUT);
     digitalWrite(RELE[i], HIGH);
  }
  
  for(int i = 0; i<2; i++){
    pinMode(MIKR[i], INPUT_PULLUP); 
  }
  pinMode(OK, INPUT_PULLUP);
}

void loop() {
    msg = serial();  
   // Serial.println(msg); 
    if(msg == "31")
    {
      dw = false;
      msg = "";
    }
    if(msg == "32")
    {
      up1 = false;
      msg = "";
    }
    if(msg == "33")
    {
      if(dw == true && opeen == true){
        msg = "";
       digitalWrite(LATCH, HIGH);
       Serial.println("ON");
       delay(100);
       digitalWrite(LATCH, LOW);
      }
      else if(up1 == true && opeen == false)
      {
       msg = "";
       digitalWrite(LATCH, HIGH);
       Serial.println("OFF");
       delay(100);
       digitalWrite(LATCH, LOW);
      }
    }
     
    
    if(digitalRead(OK) == LOW){
     dw = false;
    }
    
    if(dw == false){
     while(!digitalRead(MIKR[0]) == LOW){
       down();
     }
     st();
     dw = true;
     opeen = true;
    }

    if(up1 == false){
     while(!digitalRead(MIKR[1]) == HIGH){
       up();
     }
     st();
     up1 = true;
     opeen = false;
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



void up(){
  digitalWrite(RELE[2],LOW);
  digitalWrite(RELE[3],HIGH);
 
}
void down(){
  digitalWrite(RELE[2],HIGH);
  digitalWrite(RELE[3],LOW);
  
}
void st(){
  digitalWrite(RELE[2],HIGH);
  digitalWrite(RELE[3],HIGH);
  
}
