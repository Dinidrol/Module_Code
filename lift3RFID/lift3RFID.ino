#include <Tiny_ModBusRTU_Slave.h>
#include <TimerOne.h>
#include <SPI.h>
#include <MFRC522.h>


unsigned int regTable[10];
Tiny_ModBusRTU_Slave slave(11, 8, regTable, 10, 6);

#define LATCH1 2 //общий

#define INLATCH1 3
#define INLATCH2 4


#define RST_PIN    9    
#define SS_PIN    10    


MFRC522 mfrc522(SS_PIN, RST_PIN); 
unsigned long uidDec, uidDecTemp; 



bool Stage = false;
bool Stape = false;

bool win1 = false;
bool win2 = false;

void setup() {
  Timer1.initialize(500); // инициализация таймера 1, период 500 мкс
  Timer1.attachInterrupt(timerInterrupt, 500); // задаем обработчик прерываний
  Serial.begin(9600);
  
  SPI.begin();
  mfrc522.PCD_Init(); 
    
  pinMode(LATCH1, OUTPUT);
   digitalWrite(LATCH1, HIGH);
   
  pinMode(INLATCH1, INPUT_PULLUP);
  pinMode(INLATCH2, INPUT_PULLUP);
 
}

void loop() {


  if(regTable[1] == 1){
    Stage = true;      
  }


  if(Stape == true)
  {
    noInterrupts();
    regTable[0] = 1;
    interrupts();
  }
 

 if(Stage == true){
    digitalWrite(LATCH1, LOW);
 }

 if(digitalRead(INLATCH2) == LOW)
 {
     win2 = true; 
 }
 if(digitalRead(INLATCH1) == LOW)
 {
     win1 = true; 
 }

  
  if(win1 == true && win2 == true ){
      if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) 
      {
        delay(50);
        return;
       } 
  
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        uidDecTemp = mfrc522.uid.uidByte[i];
        uidDec = uidDec * 256 + uidDecTemp;
      }
  
      if(uidDec == 3325737337){
        Stape = true;
      }
  }

}
void timerInterrupt(){
  slave.update();
}

