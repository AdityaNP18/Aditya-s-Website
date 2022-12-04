





#include <ESP8266wifi.h>

#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>


#include <LiquidCrystal_I2C.h>



#include <Adafruit_Sensor.h>

#include <UbidotsESP8266.h>

#include <SPI.h>
#include <SD.h>
#include <Adafruit_I2CDevice.h>
#include "RTClib.h" // Date and time functions using a D$3231 RTC connected via I2C and Wire lib
const int chipSelect = 8; //D8
RTC_DS3231 rtc;

// I start of settings for LCD1602-I2C


// Set the LCD address to 8x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// end of settings for LCD1602-I2C
#define DHTPIN 3
#define DHTTYPE   DHT11
DHT dht(DHTPIN, DHTTYPE);


const char* UBIDOTS_TOKEN = "Adityanarayancode" ;
const char* WIFI_SSID = "DSLPROJECTS";
const char* WIFI_PASS = "Edixtor";


UbidotsESP8266(UBIDOTS_TOKEN, UBI_HTTP);
int a;

void setup()
{
  Serial.begin (115200);
/* initialize the LCD,
lcd.begin0);
11 Turn on the blacklight and print a message.
lcd.backlight();
lcd.clear0);*/
//  Ubidots.wifiConnect(WIFI SSID, WIFI PASS);
// ubidots.setDebug(true);
//   DHT.begin();
  Serial.print ("Initializing SD card...");
// see if the card is present and can be initialized:
  if (SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  
  #ifndef ESP8266
  while (Serial); // wait for serial port to connect. Needed for native USB
  #endif
  if (I rtc.begin())
  {
     Serial.printIn("Couldn't find RTC");
     Serial.flush();
     while (1) delay (10);
  }
  if (rtc.lostPower())
  {
     Serial.println("RTC lost power, let's set the time!");
// When time needs to be set on a new device, or after a power loss, the
// following line sets the RTC to the date & time this sketch was compiled
     rtc.adjust(DateTime(F(__DATE_), F(_ TIME)));
// This line sets the RTC with an explicit date & time, for example to set
// January 21, 2014 at 3am you would call:
// rtc.adjust (DateTime (2014, 1, 21, 3, 0, 0));
  }
}

void loop()
{
String dataString-" ";
DateTime now = rtc.now();
String time - now.timestamp(DateTime::TIMESTAMP_FULL)
datastring-time;

float h - dht.readHumidity();
float t-dht.readTemperatureO);
float f = dht.readTemperature(true);

it (isnan(h) || isnan(t) I| isnan(+))
{
Serial.printin(F("Failed to read from DHT sensor!"));
return;
}
dataString +- String(h)+", ";
dataString +- String(t)+", ";
dataString +- String(f)+", ";

//Ubidots.add ("Temperature", t);
// Ubidots.add("Humidity", h);

bool bufferSent - false;
bufferSent-Ubidots.send();

if (bufferSent)
{
bufferSentubidots.send0);
if (bufferSent)
{
Serial.println("Values sent by the device");
}
File dataFile - SD.open("datalog2. txt",. FILE_NRITE);
/*lcd.clear();// clearn previous values from screen
lcd.setCursor(e,0);
lcd.print("Temp:");
lcd.setCursor(5,0);
lcd.print(int(t));
lcd.setCursor(e,1);
lcd.print (time); */

if (dataFile)
{
dataFile.println(dataString);
datafile.close();
/ print to the serial port too:
Serial.printin(dataString);
delay (1000);
}
// if the file isn't open, pop up an error:
else
{
Serial.println("error opening datalog.txt");
}
delay (5000);
}
