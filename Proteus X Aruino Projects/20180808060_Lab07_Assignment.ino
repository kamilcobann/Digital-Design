#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);
float h,t;
const int rs=13,en=12,d4=11,d5=10,d6=9,d7=8;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
const int ledRed=4,ledGreen=5, buttonPin=7, buzzerPin=6;
int buttonState;
int ledGreenState=LOW;
int ledRedState=LOW;
int lastButtonState=LOW;
unsigned long lastDebounceTime=0;
unsigned long debounceDelay=50;
int screenMode=1;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  dht.begin();  

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Kamil COBAN");
  lcd.setCursor(0,1);
  lcd.print("20180808060");

  delay(400);
  lcd.clear();
}

void loop() {
  delay(2000);
  h=dht.readHumidity();
  t=dht.readTemperature();
  int reading = digitalRead(buttonPin);
  if(reading !=lastButtonState){
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime) > debounceDelay){
     if(reading != buttonState){
      buttonState = reading;
      if(buttonState==HIGH){
        screenMode = (-1)*screenMode;
      }
     }
  }
    if(screenMode ==1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature");
    lcd.setCursor(0,1);
    lcd.print(t);
    lcd.print("C");
  }else if(screenMode == -1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity");
    lcd.setCursor(0,1);
    lcd.print(h);
    lcd.print("%");    
  }
  lastButtonState=reading;

  if(t>30){
    digitalWrite(ledRed,HIGH);
    digitalWrite(ledGreen, LOW);
  }else{
    digitalWrite(ledGreen,HIGH);
    digitalWrite(ledRed,LOW);
  }

  if(h<30){
    tone(buzzerPin,330);
  }else{
    noTone(buzzerPin);
  }

delay(250);
}
