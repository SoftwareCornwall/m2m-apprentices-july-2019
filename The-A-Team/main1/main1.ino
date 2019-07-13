#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto left_motor_speed = 220;
  auto right_motor_speed = 200;
  auto speed = 200;
  auto turn_duration = 980;
  static const int default_forward_duration = 2000;
  int stage = 0;

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

// Draws a star


void loop(){
  if (stage ==0){
    moonwalk();
  }
  else if (stage ==1){
    figure_eight();
  }
  else if (stage ==2){
    Wheelie();
  }
  else{
  stop();
  delay(150000); 
  }
}

void follow_light(){
  
  float left_light = sensor.left_light_sensor();
  float center_light = sensor.center_light_sensor();
  float right_light = sensor.right_light_sensor();
  if (left_light <= center_light && left_light <= right_light){
    go_left();   
  }
  else if (right_light <= center_light && right_light <= left_light){
    go_right();
  }
  else {
    move(1);
  }

}

void go_left(){
  left_motor.reverse(150);
  right_motor.forward(250);
}

void go_right(){
  left_motor.forward(250);
  right_motor.reverse(100);
}

void moonwalk(){

  move (1);
  float forward_distance = sensor.forward();
  if (forward_distance <=20){
    stop();
    left_motor.forward(200);
    right_motor.reverse(200);
    delay (3300);
    stop();
    left_motor.reverse(200);
    right_motor.reverse(200);
    delay(2000);
    stop();
    left_motor.forward(200);
    right_motor.reverse(200);
    delay (1700);
    // Stop the robots motors and wait a smidge
    left_motor.stop();
    right_motor.stop();
    delay(2000);
    stage = stage + 1;
  }
 
}

void Wheelie(){
  
  left_motor.reverse(250);
  right_motor.reverse(250);
  delay (250);
  left_motor.forward(250);
  right_motor.forward(250);
  delay (2000);
  stop();
  delay(2000);
  stage = stage + 1;
}



void sensor_move()
{ 
  move(1);
  float down_distance = sensor.down();
  if (down_distance >=17){
    stop();
    reverse(550);
    // Stop the robots motors and wait a smidge
    left_motor.stop();
    right_motor.stop();
    delay(150000);
  }
}
  
void figure_eight()

{  
move_then_turn(1000);
move_then_turn(1000);
move_then_turn(1050);
move(2000);
move_then_reverse(900);
move_then_reverse(900);
move_then_reverse(900);
move(2000);
stage = stage + 1;
}
void move_then_turn(int delay_time)
{
      
      // Move robot forwards for one second
  move(2000);
  left_motor.stop();
  right_motor.stop();
  delay(500);
  turn_clockwise(delay_time);
  left_motor.stop();
  right_motor.stop();
  delay(1000);

}

void stop(){
  left_motor.stop();
  right_motor.stop();
  delay(1000);
 
}
void move(int duration){
        // Move robot forwards for one second
  left_motor.forward(left_motor_speed);
  right_motor.forward(right_motor_speed);
  delay(duration); 

}



void turn_clockwise(int delay_time){
  left_motor.forward(165);
  right_motor.reverse(200);
  delay(delay_time);
  stop();
}

void turn_anticlockwise(int delay_time){
  left_motor.reverse(200);
  right_motor.forward(165);
  delay(delay_time); 
  stop(); 
}


void move_then_reverse(int delay_time){

      // Move robot forwards for one second
  move(2000);
  left_motor.stop();
  right_motor.stop();
  delay(500);
  turn_anticlockwise(delay_time);
  left_motor.stop();
  right_motor.stop();
  delay(1000);
    // Stop the robots motors and wait a smidge

}

void reverse(int duration)
{
  left_motor.reverse(left_motor_speed);
  right_motor.reverse(right_motor_speed);
  delay(duration); 
  stop();
}


void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
