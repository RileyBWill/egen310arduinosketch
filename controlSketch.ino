#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

int state = 0;

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  myMotor->setSpeed(50);
  
  
}

void loop() {
  if (Serial.available() > 0) {
    state = Serial.read();
  }

  if (state == '0') {
    myMotor->run(RELEASE);
  }

  if (state == '1') {
    myMotor->setSpeed(100);
    myMotor->run(FORWARD);   
  }

  if (state == '2') {
    myMotor->setSpeed(50);
    myMotor->run(BACKWARD);    
  }
}
