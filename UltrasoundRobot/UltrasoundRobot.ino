// Adafruit Motor Shield library Version 1.0.0
#include <AFMotor.h>

// declaring the pins for the echo and the trigger
const int echopin = 13;
const int trigpin = 2;


// Creating motor objects
AF_DCMotor motor1(1);  
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4); 

uint8_t robotSpeed = 200;

// -------------------------------------------------------------------------------------
//                                        SETUP
// -------------------------------------------------------------------------------------

void setup() {

  setupMotors();
  setupUltraSound();
  
}

// -------------------------------------------------------------------------------------
//                                     SUPER LOOP
// -------------------------------------------------------------------------------------

void loop() {
 
  moveForward();

  if (checkDistance(measureDistance())){
    turn();
  }
  
  delay(1000);       
        
}



// -------------------------------------------------------------------------------------
//                              SETTING UP THE MOTORS
// -------------------------------------------------------------------------------------

void setupMotors() {

  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
  motor3.run(RELEASE);  
  motor4.run(RELEASE);  

  motor1.setSpeed(robotSpeed);
  motor2.setSpeed(robotSpeed);
  motor3.setSpeed(robotSpeed);
  motor4.setSpeed(robotSpeed);
  
}

// -------------------------------------------------------------------------------------
//                           SETTING UP THE ULTRA SOUND
// -------------------------------------------------------------------------------------

void setupUltraSound() {
  pinMode(trigpin,OUTPUT); // set trigpin to output
  pinMode(echopin,INPUT);  // and echopin to input
}

// -------------------------------------------------------------------------------------
//                               ROBOT MOVEMENTS
// -------------------------------------------------------------------------------------

void moveForward() {
  motor1.run(FORWARD);   
  motor2.run(FORWARD);     
  motor3.run(FORWARD);  
  motor4.run(FORWARD);   
}


void turnRight() {
    
  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
  delay(500);

  motor1.run(BACKWARD);   
  motor2.run(BACKWARD);    
  delay(1000); 

  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
}

void turnLeft() {
  
  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
  delay(500);

  motor3.run(BACKWARD);   
  motor4.run(BACKWARD);    
  delay(1000); 

  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
}

// -------------------------------------------------------------------------------------
//                         PROCESSING ULTRA SOUND DATA
// -------------------------------------------------------------------------------------

float measureDistance() {

  double duration;
  double velocity;
  double distance;
  
  // make sure that trigpin is set to LOW in the beginning
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);

  // trigger a signal in the ultrasound sensor
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  // measure the time it took the signal to travel back
  duration = pulseIn(echopin,HIGH);   // gives back time in microseconds

  velocity = 0.0343;  // speed of sound in cm/microsec
  distance = 0.5 * duration * velocity;  // distance travelled is half of duration times speed

  return distance;
  
}


bool checkDistance(float distance){

  if (distance < 90) {
    return true;
  }
  else {
    return false;
  }
  
}

bool isEven(uint8_t number) {
  if (number % 2 == 0) {
    return true;
  }

  else { 
    return false;
  }
}

void turn() {

  // create random integer to decide randomly if turning left or right
  uint8_t randomNumber = random(1,254);
  
  if (isEven(randomNumber)) {
  turnRight();
  }
  
  else {
  turnLeft();
  }
}
