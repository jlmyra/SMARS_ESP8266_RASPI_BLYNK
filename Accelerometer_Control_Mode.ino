//**************** Accelerometer - Accelerometer Control Mode****************

BLYNK_WRITE(V3) {
  x_Steer = param [0].asFloat();
  //y_Steer = param [1].asFloat();  //Accelerometer y-axis for left(-)/right(+) turns
  z_Speed = param [2].asFloat();  //Accelerometer z-axis for forward(-)/reverse(+)

  if (accel_Ready == 0 && stopGo == 0) {    //if switch is off turn off motors
      analogWrite(motorA1A, 0); 
      analogWrite(motorA1B, 0); 
      analogWrite(motorB1A, 0);
      analogWrite(motorB1B, 0);
      motorSpeed = 0; motorSpeedADJ = 0;//for meter readout
      dirNum = 0; //for LCD direction
  }
  
  if (stopGo != 1 && accel_Ready != 0 ) {  //Skip this if stopGo button is ON.
    
  Serial.print ("  x_Steer: ");
  Serial.print (x_Steer);
  Serial.print ("  z_Speed: ");
  Serial.print (z_Speed);
    
  //STOP 
 
  if ((z_Speed >= -0.3) && (z_Speed <= 0.3)) {
      analogWrite (motorA1A, 0); 
      analogWrite (motorA1B, 0); 
      analogWrite (motorB1A, 0);
      analogWrite (motorB1B, 0); 
      Serial.println (" stop  ");
      motorSpeed = 0; motorSpeedADJ = 0;//for meter readout
      dirNum = 0; //for LCD direction
     
  } else

  //FORWARD 

  if ((z_Speed < -0.3)  && (x_Steer < 0.3 && x_Steer > -0.3)) {
        
      z_Speed = ((z_Speed) * -1023);
      
      motorSpeed = map(z_Speed, 300, 1023, 0, 1023); // map the range of z_Speed 0.3 to 1 to 0 to 1 
      
      motorSpeedADJ = motorSpeed;//for meter readout
      
      Serial.print (" Forward  "); Serial.print ("  motorSpeed= "); Serial.println (motorSpeed);
      
      analogWrite (motorA1A, 0);
      analogWrite (motorA1B, motorSpeed); 
      analogWrite (motorB1A, 0);
      analogWrite (motorB1B, motorSpeed); 
      motorSpeedADJ = motorSpeed;//for meter readout
      dirNum = 1;//for LCD readout
      
  } else

  //BACKWARD
  
  if ((z_Speed) > 0.3 && (x_Steer < 0.3 && x_Steer > -0.3)) {
      
      z_Speed = ((z_Speed) * 1023);
      
      motorSpeed = map(z_Speed, 300, 1023, 0, 1023);
      
      motorSpeedADJ = motorSpeed;//for meter readout
      
      Serial.print (" BACKWARD   "); Serial.print ("  motorSpeed= "); Serial.println (motorSpeed);
      
      analogWrite (motorA1A, motorSpeed); //Turning Side slower than opposing side
      analogWrite (motorA1B, 0); //Turning Side s0er than opposing side
      analogWrite (motorB1A, motorSpeed);
      analogWrite (motorB1B, 0); 
      motorSpeedADJ = motorSpeed;//for meter readout
      dirNum = 2;//for LCD readout
     
  } else

  //FORWARD DIAGONAL RIGHT
  
  if ((z_Speed) < -0.3 && (x_Steer) > 0.3) {

      z_Speed = ((z_Speed) * -1023);
      
      motorSpeed = map(z_Speed, 300, 1023, 0, 1023);
     
      motorSpeedADJ = (motorSpeed * (1 - (x_Steer))); //z_Speed is negative here, subtracting from 1
      
      Serial.print (" Forward  diagonal right  ");Serial.print ("  motorSpeed= "); Serial.print (motorSpeed);
      Serial.print ("  motorSpeedADJ= "); Serial.println (motorSpeedADJ);

     
      analogWrite(motorA1A, 0);
      analogWrite (motorA1B, motorSpeed); 
      analogWrite(motorB1A, 0);
      analogWrite (motorB1B, motorSpeedADJ); 

      dirNum = 3;//for LCD readout
         
  } else

  //BACKWARD DIAGONAL RIGHT
  
  if ((z_Speed) > 0.3 && (x_Steer > -0.3)) {
      
      z_Speed = ((z_Speed) * 1023);

      motorSpeed = map(z_Speed, 300, 1023, 0, 1023);
   
      motorSpeedADJ = (motorSpeed * (1 - (x_Steer)));
      
      Serial.print (" BACKWARD DIAGONAL RIGHT  ");Serial.print ("  motorSpeed= "); Serial.print (motorSpeed);
      Serial.print ("  motorSpeedADJ= "); Serial.println (motorSpeedADJ);

      analogWrite (motorA1A, motorSpeed); //Turning Side slower than opposing side
      analogWrite(motorA1B, 0); //Turning Side slower than opposing side
      analogWrite (motorB1A, motorSpeedADJ);
      analogWrite(motorB1B, 0); 

      dirNum = 4;//for LCD readout
            
  } else

  //BACKWARD DIAGONAL LEFT

  if ((z_Speed) > 0.3 && (x_Steer) < 0.3) {
      
      z_Speed = ((z_Speed) * 1023);
      
      motorSpeed = map(z_Speed, 300, 1023, 0, 1023);
      
      motorSpeedADJ = motorSpeed;
      
     //motorSpeedADJ = (motorSpeed * (1 - (x_Steer)));
       motorSpeedADJ = (motorSpeed * (1 + (x_Steer)));
      
      Serial.print (" BACKWARD DIAGONAL LEFT  ");Serial.print ("  motorSpeed= "); Serial.print (motorSpeed);
      Serial.print ("  motorSpeedADJ= "); Serial.println (motorSpeedADJ);

      analogWrite (motorA1A, motorSpeedADJ); //Turning Side slower than opposing side
      analogWrite(motorA1B, 0); //Turning Side slower than opposing side
      analogWrite (motorB1A, motorSpeed);
      analogWrite(motorB1B, 0); 

      dirNum = 5;//for LCD readout
      
  } else
                                    
  //FORWARD DIAGONAL LEFT
  
  if ((z_Speed) < -0.3 && (x_Steer) < -0.3) {
      
      z_Speed = ((z_Speed) * -1023);//z_Speed is negative here - needs to be +

      motorSpeed = map(z_Speed, 300, 1023, 0, 1023);
     
      motorSpeedADJ = (motorSpeed * (1 + (x_Steer))); 
     
      Serial.print (" FORWARD DIAGONAL LEFT  ");Serial.print ("  motorSpeed= "); Serial.print (motorSpeed);
      Serial.print ("  motorSpeedADJ= "); Serial.println (motorSpeedADJ);
    
      analogWrite (motorA1A, 0);
      analogWrite(motorA1B, motorSpeedADJ); 
      analogWrite (motorB1A, 0);
      analogWrite(motorB1B, motorSpeed);
      
      dirNum = 6;//for LCD readout
     }  
  }
}

//**************** Accelerometer - Accelerometer Control Mode****************

//*************Read RUN/STOP Switch - Accelerometer Control Mode***************
  BLYNK_WRITE (V4) {    
    accel_Ready = param.asInt();
    if(accel_Ready ==1)
    {
    Blynk.setProperty(V4, "color", BLYNK_RED);  
    }
    else if(accel_Ready ==0)
    {
    Blynk.setProperty(V4, "color", BLYNK_GREEN);  
    }
  }

//*************Read RUN/STOP Switch - Accelerometer Control Mode***************
  BLYNK_READ(V6){
    
  if(RSSI_meter >= -75){
   Blynk.setProperty(V6, "color", BLYNK_GREEN);//RSSI  Meter
   Blynk.virtualWrite(V6, RSSI_meter ); 
   Blynk.setProperty(V5, "color", BLYNK_GREEN);//LCD
   }
  else if(RSSI_meter < -75 && RSSI_meter  >= -84) {
   Blynk.setProperty(V6, "color", BLYNK_YELLOW);//RSSI  Meter
   Blynk.virtualWrite(V6, RSSI_meter); 
   Blynk.setProperty(V5, "color", BLYNK_YELLOW);//LCD
  }
  else if(RSSI_meter <-82 ) {
   Blynk.setProperty(V6, "color", BLYNK_RED);//RSSI  Meter
   Blynk.virtualWrite(V6, RSSI_meter);
   Blynk.setProperty(V5, "color", BLYNK_RED);//LCD

   Blynk.virtualWrite(V4, 0); //Turn switches off button will have to be pushed when back in range
   Blynk.virtualWrite(V2, 0);
   accel_Ready = 0;// set param's to 0
   stopGo = 0;// set param's to 0
    
   //Turn off motors 
    analogWrite (motorA1A, 0); 
    analogWrite (motorA1B, 0); 
    analogWrite (motorB1A, 0);
    analogWrite (motorB1B, 0); 
    
    //Print message on LCD
    lcd.clear();
    lcd.print(0, 0, "    BATTLE BOT"); 
    lcd.print(0, 1, "   Out of Range");
  }
}

//**************************Motor Speed Meters***************************  
  BLYNK_READ(V7){  //Labelled Meter
   Blynk.virtualWrite(V7, motorSpeedADJ );   
  }
  
  BLYNK_READ(V8){  //Labelled Meter
   Blynk.virtualWrite(V8, motorSpeed );   
  }

//*************************BLYNK LCD PRINT Function***********************

  void printBlynkLCD()
  {    
  unsigned long currentMillis = millis(); //set the current time
    if (currentMillis - previousMillis > interval) 
      { //check to see if the interval has been met
      previousMillis = currentMillis; //reset the time

      if(RSSI_meter > -84)
      {
      lcd.print(0, 0, "                ");
      lcd.print(0, 1, directionLCD[dirNum]); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
      }
      else 
      {
      lcd.print(0, 0, "    BATTLE BOT"); 
      lcd.print(0, 1, "   Out of Range"); 
      }
    }
  }
//************************BLYNK LCD PRINT Function***********************

//************************RSSI METER Function****************************
  void RSSI_meterReading()
  {
  unsigned long currentMillis = millis(); //set the current time
    if (currentMillis - RSSI_previousMillis > RSSI_interval) 
      { //check to see if the interval has been met
      RSSI_previousMillis = currentMillis; //reset the time
      RSSI_meter = WiFi.RSSI();
      //Serial.print("RSSI= "); Serial.println(RSSI_meter);
      }
  }
//************************RSSI METER Function****************************
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
