#include <Tiny_ModBusRTU_Slave.h>
#include <TimerOne.h>

#include "SPI.h"

#include "TFT_ILI9341.h"

#include <MFRC522.h>

#define RST_PIN   6   // 
#define SS_PIN    5    //

unsigned int regTable[10];
Tiny_ModBusRTU_Slave slave(3, 8, regTable, 10, 2);

#define TFT_GREY 0x7BEF

TFT_ILI9341 myGLCD = TFT_ILI9341();       
MFRC522 mfrc522(SS_PIN, RST_PIN);

unsigned long runTime = 0;
unsigned long uidDec, uidDecTemp; 

int telo = 0;
bool Btelo = true;
bool Indent = false;
bool Maseg = false;
bool Maseg1 = false;

unsigned long knownCard[6] =  {
  1079653148,
  1093431066,
  545092514,
  2953163094,
  2688396118,
  3320592665
    
};
byte valid [6] = {1,1,1,1,1,1};

void setup()
{
  Timer1.initialize(500); // инициализация таймера 1, период 500 мкс
  Timer1.attachInterrupt(timerInterrupt, 500); // задаем обработчик прерываний
  Serial.begin(9600); 
   
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delay(10);
  digitalWrite(7, HIGH);

   
  SPI.begin();
  mfrc522.PCD_Init();
  
  myGLCD.init();
  myGLCD.setRotation(1);

  /*myGLCD.setTextColor(TFT_GREEN,TFT_BLUE);
  myGLCD.drawCentreString("Runtime: (msecs)", 160, 210,2);
  myGLCD.drawNumber(runTime, 130, 225,2);*/
        
}

void loop()
{
  if(Btelo == true){
     if( regTable[1] == 2)
     {
       telo = 2;
       Btelo = false; 
     }
     else if(regTable[1] == 3)
     {
       telo = 3; 
       Btelo = false; 
     }
     else if(regTable[1] == 4)
     {
       telo = 4;
       Btelo = false;
     }
     else if(regTable[1] == 5)
     {
       telo = 5;
       Btelo = false;
     }
     else if(regTable[1] == 6)
     {
       telo = 6;
       Btelo = false;
     }
  }

if(Btelo == true && Maseg == false ){

  myGLCD.fillScreen(TFT_BLACK);
  myGLCD.fillRoundRect(40, 50, 300-50,169-50, 3,TFT_RED); 
  myGLCD.setTextColor(TFT_WHITE,TFT_RED);
  myGLCD.drawCentreString("Servez-vous des 3 tubes", 160, 60, 2);
  myGLCD.drawCentreString("pneumatiques pour retrouver", 160, 75, 2);
  myGLCD.drawCentreString("le Super-Pass", 160, 90, 2);
  myGLCD.drawCentreString("Use the 3 pneumatic tubes", 160, 110,2);
  myGLCD.drawCentreString("to find the Super-key", 160, 125,2);
  Maseg = true;

}

  

if(Btelo == false) {
 if(Maseg1 == false){
  
    myGLCD.fillScreen(TFT_BLACK);
    myGLCD.fillRoundRect(40, 50, 300-50,169-50, 3,TFT_RED); 
    myGLCD.setTextColor(TFT_WHITE,TFT_RED);
    myGLCD.drawCentreString("Crew members identification:", 160, 60, 2);
    myGLCD.drawNumber(runTime, 150, 85,2);
    myGLCD.drawCentreString("", 164, 85,2);
    myGLCD.drawCentreString("Identification des membres de l'equipe:", 161, 110,2);
    myGLCD.drawNumber(runTime, 150, 135,2);
    myGLCD.drawCentreString("", 164, 135,2); 
    Maseg1 = true;
 }
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
         
  for (byte i = 0; i < telo; i++)
  {
           
    if(uidDec == knownCard[i]&& valid[i] == 1 )
      {
        runTime ++;
        valid[i] = 0;
        myGLCD.drawNumber(runTime, 150, 85,2);
        myGLCD.drawNumber(runTime, 150, 135,2);
        
        if(runTime == telo)
          {                      
              myGLCD.fillScreen(TFT_BLACK);
              myGLCD.fillRoundRect(40, 50, 300-50,169-50, 3,TFT_GREEN); 
              myGLCD.setTextColor(TFT_BLACK);
              myGLCD.drawCentreString("All members are identified.", 160, 60, 2);
              myGLCD.drawCentreString("The elevator is ready to start.", 160, 75, 2);
              myGLCD.drawCentreString("Close the door!", 160, 90, 2);
              myGLCD.drawCentreString("Tous les membres sont identifies.", 160, 110,2);
              myGLCD.drawCentreString("L'ascenseur est pret a demarrer.", 160, 125,2);
              myGLCD.drawCentreString("Fermer le sas.", 161, 140,2);
              runTime = 0;
              Indent = true;
              for(byte i = 0; i < 6; i++)
              {
                valid[i] = 0;
              }
             }
            
           }
  }
} 

  if (Indent == true){
     noInterrupts();
     regTable[0] = 1;
     interrupts();
  }  
      
   delay(500);
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {   
        //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        //Serial.print(buffer[i], HEX);
    }
}

void timerInterrupt(){
  slave.update();
}

