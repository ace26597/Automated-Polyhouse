#include<LiquidCrystal.h>
#include<dht.h>

#define LUX A0
LiquidCrystal lcd(2,3,4,5,6,7);

#define DHT22PIN 12
dht1wire DHT(DHT22PIN, dht::DHT22);

#define light 11
#define fan 8
#define heater 10
#define soil 9
#define motor 13

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 1; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'A'},
  {'B'},
  {'C'},
  {'D'}
};
byte rowPins[ROWS] = {A2,A3,A4,A5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A1}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int temperature, humidity, temp,Temp;
int check;
int test,test1,test2,test3;
float volt,lux,value;

byte degree[8] =
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
 
  pinMode(soil, INPUT);
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);
 pinMode(motor, OUTPUT);
  lcd.createChar(1, degree);
  lcd.setCursor(0,0);
  lcd.print("Green House   ");
  lcd.setCursor(0,1);
  lcd.print("  Monitering");
  delay(1000);
  lcd.clear();
}

void customkey()
{
char customKey = customKeypad.getKey();
    if (customKey == 'A'){
    Serial.println("A");
    digitalWrite(fan, !digitalRead(fan));
    delay(2000);
  }
  else if (customKey == 'B'){
    digitalWrite(heater, !digitalRead(heater));
    delay(2000);
  }
  else if (customKey == 'C'){
    digitalWrite(light, !digitalRead(light));
    delay(2000);
  }
  else if (customKey == 'D'){
    digitalWrite(motor, !digitalRead(motor));
    delay(2000);
  }
}
void loop()
{
  /*-----Light Intensity------*/
  char customKey = customKeypad.getKey();
  DHT.read();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" humidity=");
  lcd.print(humidity=DHT.getHumidity()/10);
  Serial.println("H ");
  Serial.print(humidity);
  lcd.print(" % ");
// lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("temperature=");
  lcd.print(temperature=DHT.getTemperature()/10);
  lcd.write(1);
  lcd.print("C ");
  Serial.println("T");
  Serial.print( temperature);
  delay(1000);
   value=analogRead(LUX);
   volt=(value/1023.0)*5;
   lux=((2500/volt)-500)/3.3;
   delay(10);
   customkey();
   if(lux<100)
   {
      Serial.println(lux);
     digitalWrite(light, LOW);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Low light ");
     lcd.print(lux);
     lcd.print(" LUX");
     lcd.setCursor(0,1);
     lcd.print("Lights turned ON");
     check=1;
     test=1;
     delay(1000);
   }
   else
   {
    if(check==1)
    {
     check=0;
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("light int: ");
     lcd.print(lux);
     lcd.print(" LUX");
     lcd.setCursor(0,1);
     lcd.print("Lights turned OFF");
    }
     digitalWrite(light, HIGH);
     test=0;
     delay(1000);
   }
 customkey();
  if(temperature > 35)
  {
    digitalWrite(heater,HIGH);
    digitalWrite(fan, LOW);  
     Serial.write(26);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Temp increases ");
     lcd.setCursor(0,1);
     lcd.print("Fan Turned ON  ");
     delay(2000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Temperature");
     lcd.setCursor(0,1);
     lcd.print(temperature);
     lcd.write(1);
     lcd.print("C");
     check=2;
     test2=1;
     delay(1000);
   }
   else if(temperature < 20)
   {
    digitalWrite(heater,LOW);
    lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Temp Decreased ");
     lcd.setCursor(0,1);
     lcd.print("heater Turned ON  ");
     delay(2000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Temperature");
     lcd.setCursor(0,1);
     lcd.print(temperature);
     lcd.write(1);
     lcd.print("C");
     delay(1000);
   }
   else
   {
    if(check==2)
    {
     check=0;
     test1=0;
    }
    digitalWrite(heater, HIGH);
   digitalWrite(fan, HIGH);
   delay(1000);
   }
 
customkey();
if(digitalRead(soil)==1)
   {
    digitalWrite(motor, LOW);
    check=4;
    test3=1;
    lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Water Required ");
     lcd.setCursor(0,1);
     lcd.print("Motor turned ON");
     delay(1000);
   }
    
  else
  {
    if(check==4)
    {
      digitalWrite(motor, HIGH);
     check=0;
    }
   digitalWrite(motor, HIGH);
   test3=0;
  }
  delay(100);
  customkey();
}

