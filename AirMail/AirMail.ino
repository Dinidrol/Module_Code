#include <Tiny_ModBusRTU_Slave.h>
#include <TimerOne.h>

unsigned int regTable[10];
Tiny_ModBusRTU_Slave slave(8, 8, regTable, 10, 7);

#define REL1 2
#define REL2 3

#define BUTTON 4





bool Stage = false;


void setup() {
  Timer1.initialize(500); // инициализация таймера 1, период 500 мкс
  Timer1.attachInterrupt(timerInterrupt, 500); // задаем обработчик прерываний
  Serial.begin(9600);
  

  
  pinMode(REL1, OUTPUT);
   digitalWrite(REL1, HIGH);
  pinMode(REL2, OUTPUT);
   digitalWrite(REL2, HIGH);  
 pinMode(BUTTON,INPUT_PULLUP);
}

void loop() {

  if(Stage == true){
     noInterrupts();
     regTable[0] = 1;
     interrupts();
    }
 


  if(digitalRead(BUTTON) == LOW && regTable[1] == 1){
   
    Stage = true;
    vykluchit();
    delay(500);
    vkluchit();
  } else if( digitalRead(BUTTON) == HIGH && regTable[1] == 0 ){
    
    vkluchit();
  }
  
  
}

void timerInterrupt(){
  slave.update();
}

void vykluchit() {
  digitalWrite(REL1, HIGH);
  digitalWrite(REL2, HIGH);
}
void vkluchit(){
  digitalWrite(REL1, LOW);
  digitalWrite(REL2, LOW);
}

