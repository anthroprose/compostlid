/*
  Maxbotix simple test

  Instructions:
  - At least one of: (comment the appropriate code below)
    * PW is digital pin 8
    * TX is digital pin 6
    * AN is analog pin A0
  - Change code below according to your model (LV, XL and
  HRLV supported)

  Note:"
  For convenience, the getRange method will always return centimeters.
  You can use convert fuctions to convert to another unit (toInches and
  toCentimeters are available)

*/
#include "Maxbotix.h"

Maxbotix rangeSensorPW(8, Maxbotix::PW, Maxbotix::LV);

#define clockpin 13 // CI
#define enablepin 10 // EI
#define latchpin 9 // LI
#define datapin 11 // DI
 
#define NumLEDs 1
 
int LEDChannels[NumLEDs][3] = {0};
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;

int sms = 0;
  
void setup() {
  
  Serial.begin(9600);

  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(enablepin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
  digitalWrite(latchpin, LOW);
  digitalWrite(enablepin, LOW);
   
}

void loop() {
  
  unsigned long start;
 
  start = millis();
  float distance = rangeSensorPW.getRange();

  if (sms == 1 && distance < 20) {
    Serial.println(1);
    delay(1000);
  } else if (distance < 20) {
    sms = 1;
    Serial.println(0);
    Serial.println(sms);
    delay(1000);
  } else {
    sms = 0;
    Serial.println(0);
    delay(1000);
  }
  
  delay(1000);
  
}
