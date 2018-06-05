
const double dBAnalogQuiet = 10; 
const double dBAnalogModerate = 12;
const double dBAnalogLoud = 17;
int count;

#define PIN_ANALOG_IN A0
#define PIN_QUIET 10
#define PIN_MODERATE 11
#define PIN_LOUD 12

float calculateDecibels(int x, char c)
{
  float decibelsCalculated;
  
    if (c == 'q')
      decibelsCalculated = 20 * log10(x/dBAnalogQuiet);
    if (c == 'm')
      decibelsCalculated = 20 * log10(x/dBAnalogModerate);
    if (c == 'l')
      decibelsCalculated = 20 * log10(x/dBAnalogLoud);  
  
  return (decibelsCalculated);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(PIN_QUIET, OUTPUT);
  pinMode(PIN_MODERATE, OUTPUT);
  pinMode(PIN_LOUD, OUTPUT);  
  pinMode(A0, INPUT);
  count = 0;
}

void loop() 
{
  int value, i;
  float decibelsValueQuiet = 49.5;
  float decibelsValueModerate = 65;
  float decibelsValueLoud = 70;
  float valueDb;
  
  value = analogRead(PIN_ANALOG_IN);
    
  if (value < 13)
  {
    digitalWrite(PIN_QUIET, HIGH);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, LOW);

    Serial.print("Quiet. Value: ");
    Serial.print(value);
    Serial.print("  ");
    decibelsValueQuiet += calculateDecibels(value, 'q');
    Serial.println(decibelsValueQuiet);
    valueDb = decibelsValueQuiet;
    count = count+1;
  }
  else if ((value > 13) && ( value <= 23) )
  {
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, HIGH);
    digitalWrite(PIN_LOUD, LOW);

    Serial.print("Moderate. Value: ");
    Serial.print(value);
    Serial.print("  ");
    decibelsValueModerate += calculateDecibels(value, 'm');
    Serial.println(decibelsValueModerate);

    valueDb = decibelsValueModerate;
    count = count+1;
  }
  else if(value > 22)
  {
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, HIGH);

    Serial.print("Loud. Value: ");
    Serial.print(value);
    Serial.print("  ");

    decibelsValueLoud += calculateDecibels(value, 'l');

    
    Serial.println(decibelsValueLoud);
    
    valueDb = decibelsValueLoud;
    count = count+1;
  }

 
  Serial.println(count);  
}
