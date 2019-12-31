
/*
SMARS Tracked Vehicle Controller via BLYNK and Wemos D1 mini WiFi 
On your phone in the Blynk app you need the following 4 widgets:
-SliderL on Virtual Pin: V0, Labelled Left -1023 to +1023
-SliderL on Virtual Pin V1, Labelled Right -1023 to +1023
-Switch on Virtual Pin V2, Labelled Run/Stop
-Accelerometer on Virtual Pin V3
-Switch on Virtual Pin V4 Labelled Run/Stop
The SMARS will operate in two modes with this setup
-Slider switches to increase or decrease and reverse track speed independent of each other to skid steer
and,
-Making use of the iPhone y and z axis accelerometers such that changing the orientation of the iphone
z-axis will increase or decrease and reverse track speed and y-axis will turn the bot left or right by
reducing the track speed relative to the amount of y-axis change.

Uses L9110 2-CHANNEL MOTOR DRIVER. Spec sheet-https://tinyurl.com/y88pgaka


// **********See the license at the bottom**********
*/
//**********Libraries**********

//#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"

//**********Blynk***********

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = SECRET_ssid;// create a secrets.h file with #define SSECRET_ssid"   ";
char pass[] = SECRET_pass;// create a secrets.h file with #define SECRET_pass"   ";
char auth[] = SECRET_auth;// create a secrets.h file with #define SECRET_auth"   ";

#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"

WidgetLCD lcd(V5);

const char *directionLCD[] = {"      STOP      ", "    FORWARD     ", "    BACKWARD    ", " FORWARD RIGHT  ",                                                                                        
                              " BACKWARD RIGHT ", "  BACKWARD LEFT ", "  FORWARD LEFT  "};                                                                                                                
int dirNum;//variable for which direction to display on LCD

unsigned long previousMillis = 0; //for timer reading LCD
unsigned long interval = 100; // millis between read LCD

unsigned long RSSI_previousMillis = 0; //for timer reading RSSI
unsigned long RSSI_interval = 100; // millis between read RSSI

int RSSI_meter;

//**********Blynk***********

//********************MOTORS***************************
#define motorA1A D1 //A1A Front Motor + 
#define motorA1B D2 //AIB Front Motor - 
#define motorB1A D5 //B1A Rear Motor +
#define motorB1B D6 //B1B Rear Motor -
//********************MOTORS***************************

//*************Slider Control Mode Variables****************
int leftMotorSpeed; //PWM value for motor speed
int rightMotorSpeed; //PWM value for motor speed
int stopGo = 0; //Blynk Switch for slider controls
//*************Slider Control Mode Variables****************

//*************Accelerometer Control Mode Variables*********
float x_Steer;  //Y-Axis accelerometer value
float z_Speed;  //Z-Axis accelerometer value
int motorSpeed; // PWM value from z_Speed for drive track
int motorSpeedADJ; //y-Steer adjusted PWM for skid turn track
int accel_Ready = 0; // Blynk V4 Switch On-Off Accelerometer Mode
//*************Accelerometer Control Mode Variables*********

//*****************************************************************************
//********************************VOID SETUP***********************************
//*****************************************************************************
void setup() {
  
Serial.begin(115200);
  
pinMode(motorA1A,OUTPUT); //Set Wemos D1 PIN to OUTPUT
pinMode(motorA1B,OUTPUT); //Set Wemos D2 PIN to OUTPUT
pinMode(motorB1A,OUTPUT); //Set Wemos D5 PIN to OUTPUT
pinMode(motorB1B,OUTPUT); //Set Wemos D6 PIN to OUTPUT
 
Blynk.begin(auth, ssid , pass, IPAddress(192,168,4,1), 8080); //START BLYNK

lcd.clear(); //Use it to clear the LCD Widget

}
//**********************************************************************
//*************************END VOID SETUP*******************************
//**********************************************************************

//**********************************************************************
//***************************VOID LOOP**********************************
//**********************************************************************

  void loop()
  {

  Blynk.run();

  printBlynkLCD();
  
  RSSI_meterReading();
 
  }

//**************************************************************************
//*************************END VOID LOOP************************************
//**************************************************************************

 
/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to 
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
 * to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


 */
