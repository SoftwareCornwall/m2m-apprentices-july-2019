#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;
  
  auto speedLeft = 200; //silver
  auto speedRight = 200;
  auto speed = 200;

  int phaseCount = 0; 

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void setup()
{
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
  sensor.down();
}

void motorStop(int pause){
  left_motor.stop();
  right_motor.stop();
  delay(pause);
}

void moveForward(){
    left_motor.forward(speedLeft);
    right_motor.forward(speedRight);
}

void moveBackward(){
  left_motor.reverse(speedLeft);
  right_motor.reverse(speedRight);
}

void turnRight(int duration){
 //Turn right
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(duration);
}

void turnLeft(int duration){
  right_motor.forward(speed);
  left_motor.reverse(speed);
  delay(duration);
   
}

void straightline(int distance){
  //960 = 2m
  while(left_motor.get_pulse_count() <= distance){ 
  
    moveForward();
   
    if (left_motor.get_pulse_count() > right_motor.get_pulse_count()) {
      speedLeft = 197;
      speedRight = 203;
    } 
        
    else if (right_motor.get_pulse_count() > left_motor.get_pulse_count()) {
      speedLeft = 203;
      speedRight = 197;
    } 
    
    else {
      speedLeft = 200;
      speedRight = 200;
    }
  }   
}

void figureOfEight(){
  //Right-hand square - Corner 1
  moveForward();
  delay(2000);
  motorStop(250);
  turnRight(910);
  motorStop(250);
  
  //Right-hand square - Corner 2
  moveForward();
  delay(2000);
  motorStop(250);
  turnRight(900);
  motorStop(250);
  
  //Right-hand square - Corner 3
  moveForward();
  delay(2000);
  motorStop(250);
  turnRight(950);
  motorStop(250);
  
  //Right-hand square - Final side
  moveForward();
  delay(2000);
  motorStop(250);
  
  //Left-hand square - Corner 1
  moveForward();
  delay(2000);
  motorStop(250);
  turnLeft(875);
  motorStop(250);
  
  //Left-hand square - Corner 2
  moveForward();
  delay(2000);
  motorStop(250);
  turnLeft(875);
  motorStop(250);
  
  //Left-hand square - Corner 3
  moveForward();
  delay(2000);
  motorStop(250);
  turnLeft(850);
  motorStop(250);
  
  //Left-hand square - Final side
  moveForward();
  delay(1800);
  motorStop(1000);
}

void dontJump(){
  //Wait for a bit to give the sensor a chance
  delay(50);

  //Debug output
  //Serial.println(sensor.down());

  //Move forwards whilst the distance to ground is less than 15CM
  while (sensor.down() < 15.0) {
    moveForward();
    delay(50);
    // Serial.println("forwards");
  }

  //Wait for a second before moving backwards
  motorStop(1000);

  //Scoot backwards a bit 
  moveBackward();
  delay(750);
  
  //Stop indefinitely
  
  //Serial.println("stop");
}

void wheely(){

  speedLeft =255;
  speedRight =255;
  moveBackward();
  delay(750);
  moveForward();
  delay(1000);
  motorStop(1000);
  moveForward();
  delay(2000);
  motorStop(99999);
  
}
void moonWalk(){
    moveForward();
    delay(50);
  while (sensor.forward() >=0.0 ) {
    if(sensor.forward()>15.0&&sensor.forward()<20.0){
      motorStop(1000);
      break;
    }
    
    delay(50);
    // Serial.println("forwards");
    
  }
  turnRight(3550);
  motorStop(500);
  moveBackward();
  delay(2000);
  turnRight(1750);
  
}


void twist(int duration){
  int count = 0;
  left_motor.forward(255);
  right_motor.reverse(255);
  while(count <= duration){
    left_motor.stop();
    delay(50);
    left_motor.forward(255);
    count++;
  }
  left_motor.stop();
  right_motor.stop();
}

void twistReverse(int duration){
  int count = 0;
  left_motor.reverse(255);
  right_motor.forward(255);
  while(count <= duration){
    right_motor.stop();
    delay(50);
    right_motor.forward(255);
    count++;
  }
  left_motor.stop();
  right_motor.stop();
  
}

void loop()
{
  
  dontJump();
  motorStop(200);
  turnRight(1900);
  moonWalk();
  motorStop(500);
  figureOfEight();
  motorStop(100);
  twist(50);
  twistReverse(50);
  twist(50);
  twistReverse(50);
  twist(50);
  twistReverse(50);
  motorStop(60000);

}



void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
