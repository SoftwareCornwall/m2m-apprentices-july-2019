#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed_left = 152;
  auto speed_right = 210;
  auto speed = 200;
  int counter = 0;
  int counter2 = 0;
  unsigned long time = millis();
  

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
}


void loop()
{

demo();


// Stop the robots motors
  left_motor.stop();
  right_motor.stop();
  delay(60000);
}
    
//This is our Demo code.
//It brings in various functions set out below.

void demo()
{
  drop();
  turnRight180();
  wheelie();
  figure8();
  moonwalk();
  circle();
  wheelie();
}

//Our Functions are set out below.

//Function1: The robot will go in a circle for 14 seconds.
void circle()
{
  left_motor.forward(80);
   right_motor.forward(250);
   delay(14000);
}

//Function2
/*The robot stops when it sensors an object within 6 centimetres, turns 360 degrees, reverses
and turns 180 degrees.*/
void moonwalk()
{

while (counter2 != 1) {
if (sensor.forward() <=6) {
  left_motor.stop();
  right_motor.stop();
  delay(1000);
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(2660);
  stopSmidge();
  left_motor.reverse(speed_left);
  right_motor.reverse(speed_right);
  delay(2000);
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(1400);
  left_motor.stop();
  right_motor.stop();
  delay(1000);
  counter2 ++;
}

else
{
moveForward();
}
}
}

//Function3
//The robot senses a drop of more than 6cm, stops, reverses and then stops.
void drop()
{
while (counter != 1) {

if (time >= 1000 && sensor.down() >=17) {
  left_motor.stop();
  right_motor.stop();
  delay(1000);
  left_motor.reverse(speed_left);
  right_motor.reverse(speed_right);
  delay(4200);
  left_motor.stop();
  right_motor.stop();
  delay(1000);
  counter ++;
}

else 
{
  left_motor.forward(speed_left);
  right_motor.forward(speed_right);
  time = millis();
}
}
}
//Fuction4
//Robot does a wheelie by going back at max speed and then forward for 1 second.   
void wheelie()
{
// Move robot backwards for one second
  left_motor.reverse(255);
  right_motor.reverse(255);
  delay(500);

  // Move robot forwards for one second
  left_motor.forward(255);
  right_motor.forward(255);
  delay(1000);
  
}
//Function5
//Robot moves forward in a straight line.
void moveForward()
 { 
    left_motor.forward(speed_left);
    right_motor.forward(speed_right);
  
    unsigned long left_motor_pulses = left_motor.get_pulse_count();
    unsigned long right_motor_pulses = right_motor.get_pulse_count();

    if (left_motor_pulses - right_motor_pulses >= 15)
    {
      speed_left = 150;
      speed_right = 205;
    } else if (right_motor_pulses - left_motor_pulses >= 15)
    {
      speed_left = 195;
      speed_right = 157;
    } else 
    {
      speed_left = 152;
      speed_right = 200;
    }
 }
//Function6
//Robot moves in a figure-8 formation.
void figure8(){
 moveForward2();
  turnRight();
  moveForward1();
  turnRight();
  moveForward1();
  turnRight();
  moveForward2();
  turnLeft();
  moveForward1();
  turnLeft();
  moveForward1();
  turnLeft();
}
void turnRight(){
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(700);
  stopSmidge();
}
void turnRight180(){
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(1400);
  stopSmidge();
}
void turnLeft(){
  right_motor.forward(speed);
  left_motor.reverse(speed);
  delay(850);
  stopSmidge();
}
void moveForward1(){
  left_motor.forward(speed_left);
  right_motor.forward(speed_right);
  delay(1000);
  stopSmidge();
}
void moveForward2(){
  left_motor.forward(speed_left);
  right_motor.forward(speed_right);
  delay(2000);
  stopSmidge();
}
void stopSmidge(){
  left_motor.stop();
  right_motor.stop();
  delay(500);
}  

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
