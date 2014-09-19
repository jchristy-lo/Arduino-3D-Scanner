// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo tiltServo;
Servo panServo; 
 
int tilt = 0;
int pan = 0;
int const tiltRes = 5;
int const panRes = 5;
int const pause = 5;
 
void setup() 
{ 
  tiltServo.attach(3);
  panServo.attach(5);
} 
 
 
void loop() 
{ 
  for(tilt = 0; tilt < 180; tilt += 2*tiltRes)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    tiltServo.write(tilt);              // tell servo to go to position in variable 'pos' 
    delay(pause);    // waits 15ms for the servo to reach the position 
    for(pan = 0; pan < 180; pan += panRes)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      panServo.write(pan);              // tell servo to go to position in variable 'pos' 
      delay(pause);                       // waits 15ms for the servo to reach the position 
    } 
    tiltServo.write(tilt + tiltRes);
    for(pan = 180; pan >=1; pan -= panRes)     // goes from 180 degrees to 0 degrees 
    {                                
      panServo.write(tilt);              // tell servo to go to position in variable 'pos' 
      delay(pause);                       // waits 15ms for the servo to reach the position 
    } 
  }  
  

} 
