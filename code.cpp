#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,8,9,10,11);
  
int celsius = 0;

int redled = 2;
int greenled = 3;
int yellowled = 7;
int tempRed = 12;
int tempGreen = 13;
int buzzer = 4;
int sensor = A0;
int temperature = A1;
int sensorThresh = 400;
int sensorMedium = 350;

void setup()
{
  pinMode(redled, OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(tempRed, OUTPUT);
  pinMode(tempGreen, OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(temperature, INPUT);
  lcd.begin(16,2);
  
}

void loop()
{
  int analogValue = analogRead(sensor);
  Serial.print(analogValue);
  celsius = map(((analogRead(A1) - 20) * 3.04), 0, 1023, -40, 125);
  if(analogValue>sensorThresh)
  {
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
    digitalWrite(yellowled, LOW);
    tone(buzzer,1000,10000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("!EVACUATE!");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(celsius);
    delay(1000);
  }
  else if(analogValue>sensorMedium && analogValue<sensorThresh)
  {
    digitalWrite(yellowled, HIGH);
    digitalWrite(redled,LOW);
    digitalWrite(greenled,LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("!WARNING!");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(celsius);
    delay(1000);
  }
  else if(analogValue < sensorMedium)
  {
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);
    digitalWrite(yellowled, LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SAFE");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(celsius);
    delay(1000);
  }
  
  if(celsius >= 50 || celsius <= -10)
  {
    digitalWrite(tempRed, HIGH);
    digitalWrite(tempGreen, LOW);
    noTone(buzzer);
  }else
  {
    digitalWrite(tempGreen, HIGH);
    digitalWrite(tempRed, LOW);
    noTone(buzzer);  
  }
}