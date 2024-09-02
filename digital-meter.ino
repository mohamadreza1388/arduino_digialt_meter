int trigPin = 9;
int echoPin = 10;
int buzzerPin = 13;
int buttonPin = 12;
long duration, cm, inches;
#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(8,7,6,5,4,3); 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.clear();
}
 
void loop()
{   
  measurement();
  if (digitalRead(buttonPin) == 0){
    save_data();
    Serial.print("hi");
    digitalWrite(buzzerPin, 1);
    delay(1000);
    digitalWrite(buzzerPin, 0);
  }

  
}
void measurement(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = ((duration/2) / 29.1)+1;
  if(cm >= 700){
    lcd.home();
    lcd.clear();
    lcd.print("out !!!!");
    }else{
      lcd.home();
      lcd.print(cm);
      lcd.print("cm");
      }
  delay(250);
  lcd.clear();
}
void save_data(){
  int counter = 0;
  if(counter < 256){
    EEPROM.update(counter, cm);
  }else{
    counter = 0;
  }
}