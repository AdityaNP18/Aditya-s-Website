#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>

long timer = 0;
long sleep_timer_start, sleep_timer_end,sleep_timer_end2;
float x,y,z;
int activate, interrupt,stage_sleep_time, interrupt_sleep_timer,interrupt_for_deep_sleep, total_sleep, total_deep_sleep, total_light_sleep, deep_sleep, light_sleep, interrupt_timer=0;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup(void){
   Serial.begin(9600);  
   if(!accel.begin())
   {
      Serial.println("No ADXL345 sensor detected.");
      while(1);
   }
}



void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);
  accel.update();
  
  if(millis() - timer > 1000){ 
  x = accel.getGyroX();
  y = accel.getGyroY();
  z = accel.getGyroZ();
  
  if (activate == 0){ // first sleep confirmation
  if ((x<=20 || x>=-20) && (y<=20 || y>=-20) && (z<=20 || z>=-20)) {
  sleep_timer_start = millis()/1000-sleep_timer_end;
  if (sleep_timer_start == 300){
  activate = 1;}
  }
  if ((x>=20 || x<=-20) || (y>=20 || y<=-20) || (z>=20 || z<=-20)){
  sleep_timer_end =(millis()/1000); }
  }
  
  if (activate == 1){ // sleeping mode
  light_sleep = (millis()/1000)-sleep_timer_end;
  
  if (interrupt == 0){
  if (light_sleep >= 4200){
  if (interrupt_for_deep_sleep > 4200){
  if (light_sleep - interrupt_sleep_timer >= 600){
  deep_sleep = light_sleep - interrupt_for_deep_sleep;
  }
  }
  }
  }
  light_sleep = light_sleep - deep_sleep;
  
  if ((x>=20 || x<=-20) || (y>=20 || y<=-20) || (z>=20 || z<=-20)){
  interrupt_sleep_timer = (millis()/1000)-sleep_timer_end; 
  interrupt_for_deep_sleep = light_sleep;
  interrupt =interrupt+1;
  delay(8000);}
  
  
  
  if ((millis()/1000)- sleep_timer_end -interrupt_sleep_timer > 300) {
  interrupt =0; 
  }
  
  if ((millis()/1000)- sleep_timer_end - interrupt_sleep_timer <= 300){
  if (interrupt >=5){
  sleep_timer_end =(millis()/1000);
  if (light_sleep >= 900){ // second sleep confirmation
  total_light_sleep = total_light_sleep + light_sleep;
  total_deep_sleep = total_deep_sleep + deep_sleep;
  total_sleep = total_light_sleep + total_deep_sleep; }
  activate =0;
  interrupt =0;
  deep_sleep= 0;
  light_sleep= 0;
  interrupt_sleep_timer=0;
  interrupt_for_deep_sleep=0;
  }
  }
  
  }
  stage_sleep_time = light_sleep + deep_sleep; 
  if (stage_sleep_time >= 5400){
  sleep_timer_end =(millis()/1000);
  total_light_sleep = total_light_sleep + light_sleep;
  total_deep_sleep = total_deep_sleep + deep_sleep;
  total_sleep = total_light_sleep + total_deep_sleep; 
  activate =0;
  interrupt =0;
  deep_sleep= 0;
  light_sleep= 0;
  interrupt_sleep_timer=0;
  interrupt_for_deep_sleep=0; 
  }
  
  Serial.println(sleep_timer_start); // just to know code and sensor working fine
  Serial.println(",");
  if (light_sleep >= 900){ 
  Serial.println(light_sleep/60);
  Serial.println(",");
  Serial.println(deep_sleep/60);
  Serial.println(","); 
  Serial.println(total_light_sleep/60);
  Serial.println(",");
  Serial.println(total_deep_sleep/60);
  Serial.println(",");
  Serial.println(total_sleep/60);
  Serial.println(";"); }
  else {
  Serial.println(0);
  Serial.println(",");
  Serial.println(0);
  Serial.println(","); 
  Serial.println(total_light_sleep/60);
  Serial.println(",");
  Serial.println(total_deep_sleep/60);
  Serial.println(",");
  Serial.println(total_sleep/60);
  Serial.println(";");
  } 
  timer = millis();
  }

}
