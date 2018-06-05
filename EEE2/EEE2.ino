#include <MFRC522.h>


#define RST_PIN    9   // 
#define SS_PIN    10    //
#define BUTT 2

MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp; 
unsigned long key = 3325737337;

void setup() {
  Serial.begin(9600);  
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(BUTT, OUTPUT);
     digitalWrite(BUTT, HIGH);
}

void loop() {
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
     digitalWrite(BUTT, LOW);
     Serial.println("KEY");
  }

}
