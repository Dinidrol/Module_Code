#include <Tiny_ModBusRTU_Slave.h>
#include <TimerOne.h>

unsigned int regTable[10];
Tiny_ModBusRTU_Slave slave(1, 8, regTable, 10, 6);

byte RELE[] ={10,11,12,13};

int row [] ={2,3,4,5};
int but [] ={1,2,3,4};
int pass[] ={1,2,3,2,3,4,3};
int in[7];
int tik = 0;
boolean PASS = false;
boolean ENTER_KEY = false;
String DATE;
int COMANDE;

String msg;


void setup() {
  Timer1.initialize(500); // инициализация таймера 1, период 500 мкс
  Timer1.attachInterrupt(timerInterrupt, 500); // задаем обработчик прерываний
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  for(int i = 0; i<4; i++){
    pinMode(RELE[i], OUTPUT);
      digitalWrite(RELE[i], HIGH);
  }
  digitalWrite(RELE[3], LOW);
  

}

void loop() {
  
 if(PASS == true){
     noInterrupts();
     regTable[0] = 1;
     interrupts();
 }
 


  
 if(PASS == false)
 { 
    digitalWrite(RELE[3], LOW);
    digitalWrite(RELE[2], HIGH);
    digitalWrite(RELE[1], HIGH);
    digitalWrite(RELE[0], LOW);
    
  for(int i = 0; i<=3; i++)
  {
    if(digitalRead(row[i]) == LOW )
    {
      delay(500);
      in[tik] = key(i+1);
      tik++;
      
      if(tik>=7){
        tik=0;
        
        for(int i =0; i<=6; i++)
          {
           if(in[i] == pass[i]){
              PASS = true;
            
            }
             else
            {
              for(int i = 0; i<=6; i++)
              {
                in[i] = 0;
              }
              PASS = false;
              digitalWrite(RELE[3], HIGH);
              delay(100);
              digitalWrite(RELE[3], LOW);
              delay(100);
              digitalWrite(RELE[3], HIGH);
              delay(100);
              digitalWrite(RELE[3], LOW); 
            }
          
        }
        
      }
     
    }

    
  }
}

  if(PASS == true)
  {
    digitalWrite(RELE[3], HIGH);
    digitalWrite(RELE[2], LOW);
    digitalWrite(RELE[1], LOW);
    digitalWrite(RELE[0], HIGH);  
  }  
   

 
}

int key(int keyCode){
   for(int i = 0; i<=3; i++){
     if(but[i] == keyCode){
      return but[i];
     }
   }
   return '0';
}


void timerInterrupt(){
  slave.update();
}
