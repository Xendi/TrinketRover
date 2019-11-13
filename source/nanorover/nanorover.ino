//*** original Trinket-powered Micro Rover by Rick Winscot, via Adafruit
//*** modified for Arduino Nano by David Reeves 2014 
//*** Added 7 segment display readout and photoresistor-stall mechanism

#include <Adafruit_SoftServo.h>
#include <SoftwareSerial.h>
 
#define SERVO1PIN 2   // Servo control line (orange) on Nano Pin #2
#define SERVO2PIN 4   // Servo control line (orange) on Nano Pin #4

 
Adafruit_SoftServo servo_left, servo_rght;

 
// Connect the sonar signal pins to these pins on the Nano.
#define trigPin 13
#define echoPin 12


#define segPin 8  // used to connect to 7 segment display serial Rx
const int analogInPin = A0;
int sensorValue = 0; 
SoftwareSerial mySerial(7, segPin);  // Tx from arduino is pin 8, connect to Rx on SFE LED Serial
  
 
// Moderate speed forward for both servos. Given the orientation of the servos
// one will be going forward, and the other backward. You may need to adjust 
// these slightly to get the rover to move straight forward.

const int left_offset = -8;
const int right_offset = 1;
int left_speed = (120+left_offset);
int right_speed = (60+right_offset);
 
// Number in cm when the rover will reverse and try to navigate around.
const int obstacle = 20;
 
// Multiplier used to determine how far the rover will back-up.
const int back_track = 100;
 
// Duration of a ping, distance in inches, distance converted to cm.
long duration, inches, cm;
int avoid_direction, turn_angle, turn_count;
 
void setup() 
{  
  Serial.begin (9600);
  randomSeed(analogRead(0));
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(segPin, OUTPUT);
 
  
 
  // Attach servos... and off we go!
  servo_left.attach(SERVO1PIN);
  servo_rght.attach(SERVO2PIN);
  
  mySerial.begin(9600);
  delay(50);
  mySerial.print(0x76); // reset the 7 segment display
  
//    delay(1000);
//  mySerial.write(0x7A); // Brightness command bit. Must be followed by:
//  mySerial.write(0x01); // FF is dimmest, 01 is brightest. Can also use mySerial.print("z1")
//  mySerial.print("w@"); // Turn the 2nd dot on. w@ turns all off.
  mySerial.print("hiya"); //Hello world!
  
  turn_count = 0;
} 
 
void loop() 
{ 
  // Setting servos in forward motion.
  servo_left.write(left_speed );
  servo_left.refresh();
  servo_rght.write(right_speed );
  servo_rght.refresh();
  delay(15);  
 

  
  // establish variables for duration of the ping, and the distance 
  // result in inches and centimeters.
  duration = 0;
  inches = 0;
  cm = 0;
 
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);

 
  // The echo pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  duration = pulseIn(echoPin, HIGH, 10000);
  
  if (duration == 0) {
    duration = 10000;    // a 0 return means no echo was heard - default to a high value instead to avoid errors
  }
  
  // convert the time into a distance.
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);  
 
  if (cm < 1000) {    // right-align the 7seg display
    mySerial.print(" ");
  }
    
  if (cm < 100) {
    mySerial.print(" ");
  }
      
  if (cm < 10) {
   mySerial.print(" ");
  }

  String c = String(cm);
  mySerial.print(c);    // print distance in cm on 7seg display
 
 // obstacle avoidance - 50-50 chance of backing up left or right
 
  if ( cm < obstacle ) {
    // back_track * delay(15) = distance the rover will back-up during 
    // obstacle avoidance.
    
    //turn_count+=1;
    //String t = String(turn_count);
                
                
    avoid_direction=random(0,2);
       // 50% chance of backing up left or right   
    if (avoid_direction == 0) {
      turn_angle = 60;
    }
    else {
      turn_angle = -60;
    }
      
    
    for (int i = 0; i < back_track; i++) {
      
      servo_left.write(90+left_offset+turn_angle);
      servo_left.refresh();
      servo_rght.write(90+right_offset+turn_angle);
      servo_rght.refresh();  
      delay(15);
    }
  }
  
  if (cm >= 200 || cm <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(cm);
    Serial.println(" cm");
  }

 
  // read photoresistor on pin A0, vs 4.7kohm resistor
  // if photoresistor is high-resistance or absent, run motors, otherwise stop 
  //  sensorValue = analogRead(analogInPin);      
  
  while (sensorValue > 400) {
    sensorValue = analogRead(analogInPin); 
    servo_left.write(90);
    servo_left.refresh();
    servo_rght.write(90);
    servo_rght.refresh();  
    delay(150);
  }
 
   // delay(500);
}
 
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
