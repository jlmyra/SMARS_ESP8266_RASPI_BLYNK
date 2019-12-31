//**********Read BLYNK LEFT Motor Slider - Slider Control Mode **********
BLYNK_WRITE(V0) {
  leftMotorSpeed = param.asInt();
  if (stopGo != 0 && accel_Ready != 1) 
  {
  if (leftMotorSpeed > 0) {
    analogWrite(motorA1A, 0); //V0 is positive move left track forward
    analogWrite (motorA1B, leftMotorSpeed); 
  } 
  else {
    leftMotorSpeed = -leftMotorSpeed;
    analogWrite (motorA1A, leftMotorSpeed); //V0 is negative move left track backward
    analogWrite (motorA1B, 0); //Turning Side slower than opposing side
  }
 }
}
//**********Read BLYNK LEFT Motor Slider - Slider Control Mode **********

 
//**********Read BLYNK RIGHT Motor Slider - Slider Control Mode **********
BLYNK_WRITE(V1) 
{
  rightMotorSpeed = param.asInt();
  
  if (stopGo != 0 && accel_Ready != 1) 
  {
  if (rightMotorSpeed > 0) 
    {
    analogWrite (motorB1A, 0); //V1 is positive move right track forward
    analogWrite (motorB1B, rightMotorSpeed); 
    } 
  else 
    {
    rightMotorSpeed = -rightMotorSpeed;
    analogWrite (motorB1A, rightMotorSpeed); //V1 is negative move right track backward
    analogWrite (motorB1B, 0); 
    }
  }
}
//**********Read BLYNK RIGHT Motor Slider - Slider Control Mode **********


//**********Read STOP / RUN Switch - Slider Control Mode **********
BLYNK_WRITE(V2) {
  stopGo = param.asInt();
  if (stopGo == 0)
    {
      Blynk.setProperty(V2, "color", BLYNK_BLUE);
      Blynk.setProperty(V0, "color", BLYNK_BLUE);
      Blynk.setProperty(V1, "color", BLYNK_BLUE);
      Blynk.virtualWrite (V0, 0); //Set the Blynk slide switches to zero
      Blynk.virtualWrite (V1, 0); //Set the Blynk slide switches to zero
      analogWrite (motorA1A, 0); 
      analogWrite (motorA1B, 0); 
      analogWrite (motorB1A, 0);
      analogWrite (motorB1B, 0);
    }
   else if(stopGo ==1)
   {
      Blynk.setProperty(V2, "color", BLYNK_RED);
      Blynk.setProperty(V0, "color", BLYNK_GREEN);
      Blynk.setProperty(V1, "color", BLYNK_GREEN);
   }
    }
//**********Read STOP / RUN Switch - Slider Control Mode **********


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
