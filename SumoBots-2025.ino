/****************
 * debug things *
 ****************/
#define DEBUG

#ifdef DEBUG
    #define DPRINT(msg) Serial.print(msg);
    #define OK_PRINT(msg)           \
        Serial.print(F("[OKAY] ")); \
        Serial.print(F(msg));
    #define OK_PRINTLN(msg)         \
        Serial.print(F("[OKAY] ")); \
        Serial.println(F((msg)));
    #define ERR_PRINT(msg)           \
        Serial.print(F("[ERROR] ")); \
        Serial.print(F((msg)));
    #define ERR_PRINTLN(msg)         \
        Serial.print(F("[ERROR] ")); \
        Serial.println(F((msg)));
    #define DBG_PRINT(msg)           \
        Serial.print(F("[DEBUG] ")); \
        Serial.print(F((msg)));
    #define DBG_PRINTLN(msg)         \
        Serial.print(F("[DEBUG] ")); \
        Serial.println(F((msg)));
    #define WARN_PRINT(msg)         \
        Serial.print(F("[WARN] ")); \
        Serial.print(F((msg)));
    #define WARN_PRINTLN(msg)       \
        Serial.print(F("[WARN] ")); \
        Serial.println(F((msg)));
#endif

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

// left, center, right
const uint8_t dist_sensors[] = {4, 3, 2};

// DECISION TABLE
// | left | center | right | left_motor | right_motor |
// | ---- | ------ | ----- | ---------- | ----------- |
// | 0    | 0      | 0     | MOTOR_MAX  | -MOTOR_MAX  |
// | 0    | 0      | 1     | MOTOR_MAX  | MOTOR_LOW   |
// | 0    | 1      | 0     | MOTOR_MAX  | MOTOR_MAX   |
// | 0    | 1      | 1     | MOTOR_MAX  | MOTOR_MID   |
// | 1    | 0      | 0     | MOTOR_MIN  | MOTOR_MAX   |
// | 1    | 0      | 1     | ---------- | ----------- |
// | 1    | 1      | 0     | MOTOR_MID  | MOTOR_MAX   |
// | 1    | 1      | 1     | MOTOR_MAX | MOTOR_MAX   |
const uint8_t left_decision[] = { 100, 100, 100, 100, 33, 0, 50, 100};
const uint8_t right_decision[] = { -100, 33, 100, 50, 100, 0, 100, 100};

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif

    // Set up digital pins
    for (uint8_t pin : dist_sensors)
    {
        pinMode(pin, INPUT);
    }
}

void loop() { 
    // [info] i could care less about magic numbers rn i just need this to work rq
    int decision = 0;
    for (int i = 3; i >= 0; i--) {
        decision = digitalRead(dist_sensors[i]);
        decision <<= 1;
    }

    #ifdef DEBUG
        DBG_PRINT("decision=");
        DPRINT(decision);
        DPRINT("\n");
    #endif
    spin_motor(left_motor, left_decision[decision]);
    spin_motor(right_motor, right_decision[decision]);
}

void motor_test() {
    spin_motor(left_motor, 100);
    spin_motor(right_motor, 100);
    delay(250);
    spin_motor(left_motor, 0);
    spin_motor(right_motor, 0);
    delay(5000);
} 


void spin_motor(motor m, int8_t motor_percentage)
{
    int speed_percentage =
        map(constrain(abs(motor_percentage), 0, 100), 0, 100, 0, MOTOR_MAX);

        analogWrite(m.pin_forward, motor_percentage > 0 ? speed_percentage : 0);
        analogWrite(m.pin_backward, motor_percentage < 0 ? speed_percentage : 0);
}