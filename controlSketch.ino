#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// register the motor shield object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// register the current motors being used, and what shield/port they are on
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(1);
Servo myServo;

// variable used to record the data received from bluetooth modual
int state = 0;

void setup() {

  // tell the arduino to send power to the servo, and tells the servo where straight forward is
  myServo.attach(9);
  myServo.write(90);

  // begins reading from the serial port at a baud rate of 9600
  Serial.begin(9600);

  // starts the motor shield
  AFMS.begin();

  // sets initial speed for the motor
  motorRight->setSpeed(50);  
  motorLeft->setSpeed(50);
}

// main loop for the Arduino to execute once setup is complete
void loop() {

  // checks to see if data is available from the serial port,
  // and if it is sets the state variable to what is being read from
  // the serial port
  if (Serial.available() > 0) {
    state = Serial.read();
  }

// looks to see if the state variable is equal to 0
// if it is, stops motors from running and returns the
// servo to neutral position
  if (state == '0') {
    motorRight->run(RELEASE);
    motorLeft->run(RELEASE);
    myServo.write(90);
  }

// looks to see if the state variable is equal to 1
// if it is, runs the motors 'forward' at the desired speed
  if (state == '1') {
    
    motorRight->run(FORWARD);
    motorLeft->run(FORWARD);   
  }

    

// looks to see if the state variable is equal to 2
// if it is, runs the motors 'backwards' at the desired speed
  if (state == '2') {
    motorRight->run(BACKWARD);
    motorLeft->run(BACKWARD);    
  }
  
// checks the state variable, and turns the servo to the left at the desired speed
  if (state == '3') {
   myServo.write(94);
  }

// checks the state variable, and turns the servo to the right at the desired speed
  if (state == '4') {
    myServo.write(86);
  }

// turns the motors in opposite directions, rotating the vehicle
// to the left if it is capable
  if (state == '5') {
   motorRight->run(FORWARD);
   motorLeft->run(BACKWARD); 
  }


// turns the motors in opposite directions, rotating the vehicle
// to the right if it is capable
  if (state == '6') {
   motorRight->run(BACKWARD);
   motorLeft->run(FORWARD);    
  }

// sets the speed of the motors controlling the wheels to 40 or "slow"
  if (state == 's') {
    motorRight->setSpeed(40);
    motorLeft->setSpeed(40);
  }

// sets the speed of the motors controlling the wheels to 50 or "medium"
  if (state == 'm') {
    motorRight->setSpeed(50);
    motorLeft->setSpeed(50);
  }

// sets the speed of the motors controlling the wheels to 70 or "fast"
  if (state == 'f') {
    motorRight->setSpeed(70);
    motorLeft->setSpeed(70);
  }  
}
