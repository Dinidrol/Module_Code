#include <Tiny_ModBusRTU_Slave.h>
#include <TimerOne.h>

#include <SPI.h>
#include <MFRC522.h>


 
#define RST_PIN    9    
#define SS_PIN    10    

MFRC522 mfrc522(SS_PIN, RST_PIN); 
 // 269981278 MUltipass
 
unsigned int regTable[10];
Tiny_ModBusRTU_Slave slave(2, 8, regTable, 10, 6);

unsigned long uidDec, uidDecTemp; 

byte POT[]={A0,A1,A2,A3,A4,A5};

bool Stage = false;
bool Mon = false;
byte LED = 2;
byte MON = 3;


void setup() {
  Timer1.initialize(500);
  Timer1.attachInterrupt(timerInterrupt, 500);
  Serial.begin(9600);
  
  SPI.begin();
  mfrc522.PCD_Init();
 
  
  for(int i = 0; i < 6; i++){
    pinMode(POT[i], INPUT);
  }

  pinMode(LED, OUTPUT);
   digitalWrite(LED, LOW);
  
  pinMode(MON, OUTPUT);
   digitalWrite(MON, LOW);

}

//930   243   79   683   267   666

void loop() 
{
  
if(Stage == false){
  if(890 < analogRead(POT[0]) && analogRead(POT[0]) < 970 && 200 <analogRead(POT[1]) && analogRead(POT[1]) < 280 && 40<analogRead(POT[2]) && analogRead(POT[2]) < 120 && 640 < analogRead(POT[3])  && analogRead(POT[3]) < 720 && 220 < analogRead(POT[4])  && analogRead(POT[4]) < 310 && 640 < analogRead(POT[5])  && analogRead(POT[5]) < 720)
  {
    Stage = true; 
  }  
}

if(Stage == true){
  noInterrupts();
  regTable[0] = 1;
  interrupts();
  
  digitalWrite(LED, HIGH);
}

if(Stage == true){

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

 if(uidDec == 269981278){
    Mon = true; 
 }
 
}

if (Mon == true){
  noInterrupts();
  regTable[1] = 1;
  interrupts();
  digitalWrite(MON, HIGH); 
}

}

void timerInterrupt(){
  slave.update();
}

