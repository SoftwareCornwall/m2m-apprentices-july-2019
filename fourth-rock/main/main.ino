#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"
// Too much on right turns, too much on left turns. Check video for ref
namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 255;
  auto speed_right = speed-10;
  auto speed_left = speed+10;


  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};

  int millis_at_reverse = millis();
}

void setup()
{
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
  left_motor.reset_pulse_count();
  right_motor.reset_pulse_count();
  sensor.down();
  
 
  
}

//void forward(motor_speed) {
//  left_motor.forward(motor_speed);
//  right_motor.forward(motor_speed);
//}
//void reverse(motor_speed) {
//  left_motor.reverse(motor_speed);
//  right_motor.reverse(motor_speed);
//}

void loop()
{
//  forward(speed);
//  delay(500);
//  reverse(speed);
//  delay(500);
//  forward(speed);
//  delay(500);
//  reverse(speed);
//  delay(500);

  // clap your hands x1!
  Serial.println("clap hands 1");
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(500);
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(500);
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(500);
  
  // clap your hands x2!
  Serial.println("clap hands 2");
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(500);
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(500);
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(500);

  left_motor.stop();
  right_motor.stop();
  delay(2000);

  // slide to the left!
  Serial.println("slide left");
  left_motor.reverse(50);
  right_motor.forward(speed);
  delay(100);
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.stop();
  right_motor.stop();
  delay(500);
  
  // reverse
  Serial.println("reverse");
  left_motor.forward(50);
  right_motor.reverse(speed);
  delay(100);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(500);
  left_motor.stop();
  right_motor.stop();
  delay(2000);

  // hopity hop!
  Serial.println("hipity hop");
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(250);
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(250);
  left_motor.forward(speed);
  right_motor.forward(speed);
  delay(500);
  left_motor.stop();
  right_motor.stop();
  delay(2000);

  // right stomp
  Serial.println("right stomp");
  left_motor.forward(speed);
  right_motor.forward(50);
  delay(250);
  left_motor.reverse(speed);
  right_motor.reverse(50);
  delay(250);
  left_motor.stop();
  right_motor.stop();
  delay(500);

  // left stomp
  Serial.println("left stomp");
  left_motor.forward(50);
  right_motor.forward(speed);
  delay(250);
  left_motor.reverse(50);
  right_motor.reverse(speed);
  delay(500);

  // cha cha!
  Serial.println("cha cha now y'all!");
  left_motor.forward(speed);
  right_motor.forward(150);
  delay(1000);
  left_motor.reverse(150);
  right_motor.reverse(speed);
  delay(1000);
  left_motor.forward(speed);
  right_motor.forward(150);
  delay(1000);
  left_motor.reverse(150);
  right_motor.reverse(speed);
  delay(1000);
  left_motor.forward(speed);
  right_motor.forward(150);
  delay(1000);
  left_motor.reverse(150);
  right_motor.reverse(speed);
  delay(1000);
  left_motor.stop();
  right_motor.stop();
  delay(500);

  // spin
  Serial.println("you spin me right round");
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(4000);
  left_motor.stop();
  right_motor.stop();
  delay(60000);
 }

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
  
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
  right_motor.get_pulse_count();
}

/*
 
 {
  Stop the robots motors and wait a smidge
  

  Turn right for half a second
  

  Move robot backwards for one second
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(1000);
  
    // Turns the robot
  left_motor.forward(speed);
  right_motor.reverse(speed);
  delay(7500);
 }

  
 */
 

