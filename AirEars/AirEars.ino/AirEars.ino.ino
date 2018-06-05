#include <Tiny_ModBusRTU_Slave.h>
#include <TimerOne.h>

#include <Keypad.h>
unsigned int regTable[10];
Tiny_ModBusRTU_Slave slave(6, 8, regTable, 10, 13);

#define REL1 2
#define REL2 3

#define BUTTON 4
//5910984

char PASS[]={'5','9','1','0','9','8','4'};
char PASS1[7];
int tik = 0;

const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
}; 

byte rowPins[ROWS] = {5,6,7, 8}; 
byte colPins[COLS] = {9,10,11,12}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

bool Stage = false;
bool pass = false;
 

void setup() {
  Timer1.initialize(500); // инициализация таймера 1, период 500 мкс
  Timer1.attachInterrupt(timerInterrupt, 500); // задаем обработчик прерываний
  Serial.begin(9600);


  
  pinMode(REL1, OUTPUT);
   digitalWrite(REL1, HIGH);
  pinMode(REL2, OUTPUT);
   digitalWrite(REL2, HIGH);  
 pinMode(BUTTON,INPUT_PULLUP);
   vkluchit();
}

void loop() {
 char key = keypad.getKey();
 if (key){
     PASS1[tik] = key;
     tik ++;
     if(tik >= 7){
      tik = 0;
      for(int i = 0; i<7; i++){
        if(PASS[i] == PASS1[i]){
          Stage = true;
        }
      }
     }
 }
  
  if(Stage == true){
     noInterrupts();
     regTable[0] = 1;
     interrupts();
    }
 


  if(Stage == true){
    vykluchit();
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
