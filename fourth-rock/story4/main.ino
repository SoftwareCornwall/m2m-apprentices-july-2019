#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"
// Too much on right turns, too much on left turns. Check video for ref
namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;
  auto speed_right = speed-10;
  auto speed_left = speed+10;


  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};

  boolean forward = true;
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

//
void loop()
{
  Serial.println(sensor.down());
  if (sensor.down() <= 16 && forward == true){
    left_motor.forward(speed_left);
    right_motor.forward(speed_right);
    Serial.println("forward");
  }
  if (sensor.down() > 16 && forward == true){
    left_motor.stop();
    right_motor.stop();
    delay(1000);
    forward = false;
    millis_at_reverse = millis();
    Serial.println("detection");
  }
  if (millis() < millis_at_reverse + 467 && forward == false){
    left_motor.reverse(speed_left);
    right_motor.reverse(speed_right);
    Serial.println("reverse");
  }
  if (millis() > millis_at_reverse + 467 && forward == false){
    left_motor.stop();
    right_motor.stop();
  }
  delay(50);
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
 
