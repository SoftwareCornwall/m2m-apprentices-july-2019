# Rover Starter Files
The starter files for Software Cornwalls Mission to Mars rover robots. Using these,
you'll have the rovers whizzing about in no time.

## Usage Instructions
Clone the project locally and edit the main.ino file for starters.

The following examples will help you to begin working with the rovers. Try adding
some to the loop within the main.ino file. As you begin to develop your rover
instruction set, you'll likely want to encapsulate these groups of instructions
into functions.

## Default movements
By default the rover will repeat the following pattern until:

- Forwards for one second
- Stop motors
- Turn right for half a second
- Reverse for one second

### Motor Usage

**Move Rover Forwards**
Move the rover forwards at the default speed for 1 second.

    left_motor.forward(speed);
    right_motor.forward(speed);
    delay(1000);

**Reverse the Rover**
Move the rover backwards for 1 second.

    left_motor.reverse(speed);
    right_motor.reverse(speed);
    delay(1000);

**Stop Rover**

    left_motor.stop();
    right_motor.stop();

**Disable the Rover**
Prevents the rover from moving by switching the motors off. Use this once the
intended functionality has completed.

    left_motor.disable();
    right_motor.disable();

### Distance Sensor Usage

Returns an integer value for the distance between the sensor and nearest object in cm.
Note: There is a minimum delay of 50ms between each ping of the distance sensors.

    sensor.forward();
    sensor.down();

### Light Sensor Usage

    sensor.left_light();
    sensor.center_light();
    sensor.right_light();

### Interrupt Usage

Returns an integer value for the number of pulses created by the hall effect sensor.

    left_motor.get_pulse_count();
    right_motor.get_pulse_count();

You can reset the pulse count of each motor by calling:

    left_motor.reset_pulse_count();
    right_motor.reset_pulse_count();
