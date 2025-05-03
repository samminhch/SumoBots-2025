#include <Arduino.h>

/****************
 * debug things *
 ****************/
// Comment out when competing
#define DEBUG
#include "debug_printing.h"

/**********
 * Motors *
 **********/
const int MOTOR_MAX = 512;

struct motor
{
        const uint8_t pin_forward;
        const uint8_t pin_backward;
};

motor left_motor{9, 10};
motor right_motor{0, 1};

/********************
 * Distance Sensors *
 ********************/

// left, center, right sensors
const uint8_t dist_sensors[] = {A5, A6, A7};

// harper: ignore
// Decision table for hunting alorithm:
// | left | center | right | left_motor % | right_motor % |
// | ---- | ------ | ----- | ------------ | ------------- |
// | 0    | 0      | 0     | 50           | -50           |
// | 0    | 0      | 1     | 66           |  33           |
// | 0    | 1      | 0     | 100          |  100          |
// | 0    | 1      | 1     | 66           |  50           |
// | 1    | 0      | 0     | 33           |  66           |
// | 1    | 0      | 1     | -50          |  50           |
// | 1    | 1      | 0     | 50           |  66           |
// | 1    | 1      | 1     | 100          |  100          |
// The spin is different on 101 vs. 000 to tell apart the different
// status codes the robot is experiencing

// clang-format off
const int8_t left_decision[]  = { 15, 25, 100, 25, 15, -15, 15, 100};
const int8_t right_decision[] = {-15, 15, 100, 15, 20,  15, 25, 100};
// clang-format on

/****************
 * Line Sensors *
 ****************/
const uint32_t max_analog_value = 1'023;
const float ring_tolerance      = max_analog_value * 0.8;
const uint32_t line_sensors[]   = {A4, A5};  // left, right sensors

/******************
 * Helper Methods *
 ******************/
void attack();
void sanity_test();
void distance_sensor_test();
void spin_motor(motor m, int8_t motor_percentage);

void setup()
{
    // Set up digital pins
    for (uint8_t pin : dist_sensors)
    {
        pinMode(pin, INPUT);
    }

#ifdef DEBUG
    Serial.begin(9'600);
    WARN_PRINTLN("3 second delay in debug mode start");
    delay(3'000);
    OK_PRINTLN("Debug printing start!");
#endif
}

void loop() { attack(); }

void attack()
{
    // Get line sensor data
    uint32_t left_result  = analogRead(line_sensors[0]);
    uint32_t right_result = analogRead(line_sensors[1]);

    DBG_PRINT("line_sensors={left: ");
    DPRINT(left_result);
    DPRINT(", right: ");
    DPRINT(right_result);
    DPRINTLN("}");

    if (left_result < ring_tolerance && right_result < ring_tolerance)
    {
        // Stop motors if the robot is out of the ring
        spin_motor(left_motor, 0);
        spin_motor(right_motor, 0);
    }
    else
    {
        int decision = 0;
        DBG_PRINT("hunt_decision={ ");
        for (int i = 2; i >= 0; i--)
        {
            int sensor_input  = digitalRead(dist_sensors[i]);
            decision         += sensor_input * (1 << i);
            DPRINT(sensor_input);
            DPRINT(" ");
        }

        spin_motor(left_motor, left_decision[decision]);
        spin_motor(right_motor, right_decision[decision] * 0.7);

        DBG_PRINT("left_decision=");
        DPRINT(left_decision[decision]);
        DPRINT(", right_decision=");
        DPRINT(right_decision[decision]);
        DPRINTLN("}");
    }
}

void sanity_test()
{
    Serial.begin(9'600);
    for (int i = 0; i < 16; i++)
    {
        Serial.println(i);
        delay(1'000);
    }
}

void distance_sensor_test()
{
    DBG_PRINT("dist_sensors={ ");
    for (int i = 2; i >= 0; i--)
    {
        DPRINT(analogRead(dist_sensors[i]));
        DPRINT(" ");
    }
    DPRINTLN("}");
}

/**
 * @param m The motor to spin
 * @param motor_percentage The percentage speed to spin the motor at. The valid
 * range should be from -100 to 100, and will be constrained to that range.
 * Negative numbers meant that the motor will spin backwards.
 */
void spin_motor(motor m, int8_t motor_percentage)
{
    int speed_percentage =
        map(constrain(abs(motor_percentage), 0, 100), 0, 100, 0, MOTOR_MAX);

    analogWrite(m.pin_forward, motor_percentage > 0 ? speed_percentage : 0);
    analogWrite(m.pin_backward, motor_percentage < 0 ? speed_percentage : 0);
}
