
#include <TVout.h>

byte pin[] = {2,3,4};


TVout TV;

/*unsigned long knownCard[6] =  {
  3380263289,
  1980676729,
  772913785,
  1180154489,
  2953429065,
  3843406457   
};*/



void setup()
{

  TV.begin(PAL);
  
  pinMode(PIN1, INPUT_PULLUP);
  pinMode(PIN2, INPUT_PULLUP);
  pinMode(PIN3, INPUT_PULLUP);
  
  

            
  /*TV.selectFont(font6x8);
  TV.clearScreen();
  TV.selectFont(font8x8);
  TV.println(20,20, "RFID Scaner"); 
 // delay(500);
  intro(1);*/
}

void loop()
{
  if(digitalRead(PIN1)== LOW && digitalRead(PIN2)== LOW && digitalRead(PIN3)== LOW ) intro(1);
  
  if(digitalRead(PIN1)== LOW && digitalRead(PIN2)== LOW && digitalRead(PIN3)== HIGH ) intro(2);
  
  if(digitalRead(PIN1)== LOW && digitalRead(PIN2)== HIGH && digitalRead(PIN3)== LOW ) intro(3);
  
  if(digitalRead(PIN1)== HIGH && digitalRead(PIN2)== LOW && digitalRead(PIN3)== LOW ) intro(4);
  
  if(digitalRead(PIN1)== HIGH && digitalRead(PIN2)== LOW && digitalRead(PIN3)== HIGH ) intro(5);
  
  if(digitalRead(PIN1)== HIGH && digitalRead(PIN2)== HIGH && digitalRead(PIN3)== LOW ) intro(6);
  
  




  
 
}

void intro(int x){
  if(x == 1){
   
    TV.println(20,20, "Cargo section");
    TV.println(20,40, "Floor / Etage");
    TV.drawLine(60, 60, 60, 80, INVERT);
    TV.drawLine(80, 60, 73, 70, WHITE);
    TV.drawLine(73, 70, 80, 70, INVERT);
    TV.drawLine(80, 70, 73, 80, INVERT);
  }
  
  if(x == 2){
    
    TV.println(25,20, "Engineering");
    TV.println(20,40, "Floor / Etage");
    //линия 
    TV.drawLine(60, 60, 60, 80, INVERT);
    //символ
    TV.drawLine(73, 60, 80, 70, WHITE);
    TV.drawLine(73, 70, 80, 70, INVERT);
    TV.drawLine(73, 70, 80, 80, INVERT);
  }

  if(x == 3){
   
    TV.println(35,20, "Refresher");
    TV.println(20,40, "Floor / Etage");
    //линия 
    TV.drawLine(60, 60, 60, 80, INVERT);
    //символ
    TV.drawLine(73, 60, 73, 70, WHITE);
    TV.drawLine(73, 70, 80, 70, INVERT);
    TV.drawLine(80, 70, 73, 80, INVERT);  
  }
  if(x == 4){
    
    TV.println(30,20, "Maneuvering");
    TV.println(50,30, "Drive");
    TV.println(20,40, "Floor / Etage");
     //линия 
    TV.drawLine(60, 60, 60, 80, INVERT);
    //символ
    TV.drawLine(80, 60, 80, 70, WHITE);
    TV.drawLine(73, 70, 80, 70, INVERT);
    TV.drawLine(73, 70, 80, 80, INVERT);
  }
  if(x == 5){
    
    TV.println(30,20, "Hyperspace");
    TV.println(30,30, "Generator");
    TV.println(20,40, "Floor / Etage");
    //линия 
    TV.drawLine(60, 60, 60, 80, INVERT);
    //символ
    TV.drawLine(80, 60, 73, 70, WHITE);
    TV.drawLine(73, 70, 80, 70, INVERT);
    TV.drawLine(80, 70, 80, 80, INVERT);
  }
  if(x == 6){

    TV.println(30,20, "Space Milk");
    TV.println(40,30, "Storage");
    TV.println(20,40, "Floor / Etage");
    //линия 
    TV.drawLine(60, 60, 60, 80, INVERT);
    //символ
    TV.drawLine(73, 60, 80, 70, WHITE);
    TV.drawLine(73, 70, 80, 70, INVERT); 
    TV.drawLine(73, 70, 73, 80, INVERT);
  }
}

