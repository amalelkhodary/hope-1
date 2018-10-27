 
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 9, 8);
Servo servo;
VR myVR(2,3);  
uint8_t record[7]; // save record
uint8_t buf[64];
int led = 13;

void setup()
{servo.attach(10);
lcd.begin(16, 2);
  /** initialize */
  myVR.begin(9600);
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  record[0] = 0;
  record[1] = 1;
  record[2] = 2;
  record[3] = 3;
     myVR.load(record,4) ;
    servo.write(0);
}

void loop()
{lcd.setCursor(0, 0);
lcd.print("Enter Voice CMD");
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case 0:
         lcd.clear();
lcd.setCursor(0,1);
        digitalWrite(led, HIGH);servo.write(180);lcd.print("Door opened");Serial.println("Door Opened"); delay(1500);
        break;
      case 1:
         lcd.clear();
lcd.setCursor(0,1);
        digitalWrite(led, LOW);servo.write(0);lcd.print("Door Closed");Serial.println("Door Closed"); delay(1500);
        break;

        case 2:
          lcd.clear(); lcd.setCursor(0,1);
        digitalWrite(7, HIGH);lcd.print("Lights ON");Serial.println("LIGHTS ON");delay(1500);
        break;
        
        case 3:
        lcd.clear();
        lcd.setCursor(0,1);
        digitalWrite(7, LOW);lcd.print("Lights OFF");Serial.println("LIGHTS OFF");delay(1500);
        break;
                       
      default:
        break;
    }
   
    }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/

