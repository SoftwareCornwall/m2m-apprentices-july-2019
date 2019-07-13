#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"

namespace {

}

class Sensor
{
  private:
    const int forward_trigger= 4;
    const int forward_echo = 5;
  
    const int down_trigger = 13;
    const int down_echo = 17;
  
    const int max_distance = 200;
    const int max_drop = 20;

    const int left_light_pin = 7;
    const int center_light_pin = 6;
    const int right_light_pin = 2;
  
  public:
    Sensor();
  
    float forward();
    float down();
    float left_light_sensor();
    float center_light_sensor();
    float right_light_sensor();
};

#endif
