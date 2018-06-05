#include "SPI.h"
#include <Wire.h>    
#include "PCF8574.h" 
#include "TFT_ILI9341.h"

#define LATCH  2
#define LATCH1 3

#define red    4
#define green  5

TFT_ILI9341 myGLCD = TFT_ILI9341();       
PCF8574 expander;

int rows[]={7,6,5,4}; 
int cols[]={3,2,1,0}; 

char pass[2]; 
char pass1[] = {'8','9'};
int tik = 0;

byte runTime=0;
char number = 0;
int tim = 12;
char simbols[][2]={
    {0,'1'},
    {1,'4'},
    {2,'7'},
    {3,'*'},
    {4,'2'},
    {5,'5'},
    {6,'6'},
    {7,'0'},
    {8,'3'},
    {9,'8'},
    {10,'9'},
    {11,'#'},
    {12,'A'},
    {13,'B'},
    {14,'C'},
    {15,'D'}
};


char FindKey(unsigned int keyCode){
    for(int i=0;i<16;i++){
      if(simbols[i][0]==keyCode){
        return simbols[i][1];
      }
    }
    return '-'; 
}

void setup()
{
  Serial.begin(9600); 
   
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delay(10);
  digitalWrite(7, HIGH);

  pinMode(LATCH, OUTPUT);
   digitalWrite(LATCH, HIGH);
  
  pinMode(LATCH1, INPUT_PULLUP);
   
  pinMode(red, OUTPUT);
   digitalWrite(red, LOW);
  pinMode(green, OUTPUT);
   digitalWrite(green, LOW);
  
  SPI.begin();
  
  myGLCD.init();
  expander.begin(0x27);
  
  expander.pinMode(0, INPUT_PULLUP);
  expander.pinMode(1, INPUT_PULLUP);
  expander.pinMode(2, INPUT_PULLUP);
  expander.pinMode(3, INPUT_PULLUP);
  expander.pinMode(4, OUTPUT);
  expander.pinMode(5, OUTPUT);
  expander.pinMode(6, OUTPUT);
  expander.pinMode(7, OUTPUT);
  
  myGLCD.setRotation(3);
  myGLCD.fillScreen(TFT_BLACK);
  myGLCD.fillRoundRect(10, 50, 310-5,169-50, 3,TFT_RED); 
  myGLCD.setTextColor(TFT_WHITE,TFT_RED);
                          
  myGLCD.drawCentreString("Attention!", 160, 60, 2);
  myGLCD.drawCentreString("Enter sector numbers", 160, 75, 2);
  myGLCD.drawCentreString("Attention!", 160, 90, 2);
  myGLCD.drawCentreString("Entrez le secteur",160, 105 , 2 );
  //myGLCD.drawCentreString("assurez-vous que tous les membres", 160, 120, 2); 
  //myGLCD.drawCentreString("de lequipe sont identifies", 160, 135, 2);
  //myGLCD.drawCentreString("et presents!", 160, 150, 2); 
 digitalWrite(red, HIGH);
}

void loop()
{
if(digitalRead(LATCH1) == LOW){
 
  Serial.println("Vhod");
  for(int i=0;i<4;i++)
  { 
    expander.digitalWrite(rows[i], LOW);
      for(int j=0;j<4;j++)
      { 
        if( expander.digitalRead(cols[j])== LOW)
        { 
            delay(500); 
             pass[tik] = char(FindKey(4*i+j));
             tik ++;
             if(tik>=2){
              tik = 0;
              for(int k = 0; k < 2; k++){
                if(pass[k] == pass1[k]){     //Use the Super-key to start the lift
                  Serial.println("PASSOK");  //Utilisez le Super-Pass pour démarrer l'ascenseur
                    myGLCD.drawCentreString("Utilisez le Super-Pass", 160, 60, 2);
                    myGLCD.drawCentreString("pour demarrer l'ascenseur", 160, 75, 2);
                    myGLCD.drawCentreString("Use the Super-key", 160, 90, 2);
                    myGLCD.drawCentreString("to start the lift",160, 105 , 2 );
                  digitalWrite(red,  LOW);
                  digitalWrite(green, HIGH);
                  digitalWrite(LATCH, LOW);
                }
              }
             }


          
        }
      }
       expander.digitalWrite(rows[i], HIGH);
   }
  }
}
