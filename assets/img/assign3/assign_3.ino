#include <SR04.h>

const int trigPin = 9;
const int echoPin = 10;
const int led = 2;
long duration;
int distance;

SR04 sr04 = SR04(echoPin, trigPin);
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(led,OUTPUT);
      
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  distance = sr04.Distance();
  //distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.print(distance);
  lcd.clear();
  lcd.print("Distance : ");
  lcd.print(distance);
  lcd.setCursor (0,1); // go to start of 2nd line
  if(distance >45){
    lcd.print("   SAFE    :D ");
    //tone(led, 0, 0);
    noTone(led);
    //analogWrite(led, 0);
  }
  else if(distance <=45 && distance > 20 ){
    lcd.print("   AWARE   :0");
    tone(led, 15000);
    //analogWrite(led, 100);
  }
  else{
    lcd.print("   STOP    :( ");
    tone(led, 30);
    //analogWrite(led, 255);
  }
  

  delay(500);

  

}
