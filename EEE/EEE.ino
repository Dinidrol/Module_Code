#include <Tiny_ModBusRTU_Slave.h>
#include <TimerOne.h>

unsigned int regTable[10];
Tiny_ModBusRTU_Slave slave(7, 8, regTable, 10, 6);

byte HALL[]={2,3,4};

bool Stage = false;

void setup() {  
  
  Timer1.initialize(500);
  Timer1.attachInterrupt(timerInterrupt, 500);
  Serial.begin(9600);
 
  for(int i = 0; i<4; i++){
    pinMode(HALL[i],INPUT);
  }
  

}

void loop() {
     
  if (digitalRead(HALL[0]) == LOW && digitalRead(HALL[1]) == LOW && digitalRead(HALL[2]) == LOW && Stage == false){
    Stage = true;
  }
  
   if(Stage == true){
     noInterrupts();
     regTable[0] = 1;
     interrupts();
     Stage == true;
    }

  
}

void timerInterrupt(){
  slave.update();
}
