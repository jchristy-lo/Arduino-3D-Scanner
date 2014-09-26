#include <Servo.h> 

// Initialize Servo objects
Servo tiltServo;
Servo panServo; 
// Pin Definition
const int tiltPin = 3;
const int panPin = 5;
const int sensorPin = A0;
// Scan Parameters
int tiltRes = 5;
int tiltMin = 0;
int tiltMax = 180;
int panRes = 5;
int panMin = 0;
int panMax = 180;
int pause = 2;
const int sampleSize = 40; // # of samples to read at each point
// State Variables
int tilt = 0; // current tilt angle
int pan = 0; // current pan angle
int reading = 0; // current sensor reading
// Intermediate Variables
int samples[sampleSize]; // storage for readings
int total = 0; // averaging intermediate

void setup() { 
  tiltServo.attach(tiltPin);
  panServo.attach(panPin);
  Serial.begin(115200); // Initialize Serial
  Serial.print("Enter \'+\' and commands to set scan parameters ");
  Serial.println("or send any other character to begin.");
  while (!Serial.available()) {
    //
  }
  Serial.println("Start of Scan: ");
}
 
void loop() { 
  for(tilt = tiltMin; tilt < tiltMax; tilt += 2*tiltRes) {  // sweep tilt range
    tiltServo.write(tilt);
    reading = getReading();
    //Serial.println("Tilt: "+String(tilt)+" | Pan: "+String(pan)+" | Reading: "+String(reading));
    Serial.println(String(tilt)+","+String(pan)+","+String(reading));
    delay(pause); // delay for the servo to reach the position 
    for(pan = panMin; pan <= panMax; pan += panRes) { // sweep pan range L-R
      panServo.write(pan); 
      reading = getReading();
      //Serial.println("Tilt: "+String(tilt)+" | Pan: "+String(pan)+" | Reading: "+String(reading));
      Serial.println(String(tilt)+","+String(pan)+","+String(reading));
      delay(pause); // delay for the servo to reach the position 
    }
    tilt+=tiltRes; // increment tilt to follow L-R-L-... scan pattern
    tiltServo.write(tilt); 
    reading = getReading();
    //Serial.println("Tilt: "+String(tilt)+" | Pan: "+String(pan)+" | Reading: "+String(reading));
    Serial.println(String(tilt)+","+String(pan)+","+String(reading));
    delay(pause); // delay for the servo to reach the position 
    for(pan = panMax; pan >= panMin; pan -= panRes) { // sweep pan range R-L                               
      panServo.write(pan);
      reading = getReading();
      //Serial.println("Tilt: "+String(tilt)+" | Pan: "+String(pan)+" | Reading: "+String(reading));
      Serial.println(String(tilt)+","+String(pan)+","+String(reading));
      delay(pause); // delay for the servo to reach the position 
    }
  }
  Serial.println("END OF SCAN");
} 

int getReading() {
  total = 0;
  for(int i=0; i<sampleSize; i+=1) { // record sampleSize samples
    samples[i] = analogRead(sensorPin);
    total += samples[i];
  }
  return total/sampleSize;
}