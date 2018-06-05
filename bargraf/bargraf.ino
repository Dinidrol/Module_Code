byte LED[] = {2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2};   // светодиод на пинах
byte REL1 = A3;  
byte REL2 = A4;  
byte MIC  = A6; 
int volum = 0;    
      
void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < 15; i++) {   // сделать все светодиодные пины выходами и выключить
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], 0);
  }
  pinMode(A3, OUTPUT);
    digitalWrite(A3, HIGH);
  pinMode(A4, OUTPUT);
    digitalWrite(A4, HIGH);
  pinMode(A6, INPUT);
      
}
// функция плавной вспышки светодиода, на вход цвет и яркость, а также пищалка
void fade (int color, int bright) {
  for (byte i = 0; i < 252; i += 2) {
    analogWrite(LED[color], i);
    delay(1);
  }

  for (byte i = 254; i > 3; i -= 2) {
    analogWrite(LED[color], i);
    delay(1);
  }
  digitalWrite(LED[color], 0);
}

void loop() {
  volum = analogRead(A6);
  volum = map(volum,0,600,0,15);
  Serial.println(volum);
  
 for(byte i = 0; i < 15; i++){
   if(volum >= i){
   digitalWrite(LED[i], HIGH);
   delay(2);
} else{
 

  digitalWrite(LED[i], LOW);
  delay(2);
 }
 }
 if(volum >=14){
   digitalWrite(A3, LOW);
 }
}
