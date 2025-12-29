#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Motor A (Left Motor)
#define ENA_PIN 13   // PWM
#define IN1_PIN 12  // Forward
#define IN2_PIN 11   // Backward


// Motor B (Right Motor)
#define ENB_PIN 9    // PWM
#define IN3_PIN 10  // Forward
#define IN4_PIN 8   // backward

// Ultrasonic Sensor
#define TRIG_PIN 7
#define ECHO_PIN 6

#define IR_PIN 5   // IR sensor OUT -> D5 (Leonardo)

// --- tuning values (adjust to your car) ---
const int SPEED_MOVE = 150;
const int SPEED_TURN = 150;

const int TURN_TIME_MS = 500;     // how long a "right try" turn is
const int PAUSE_MS     = 500;     // small pause between actions
// If unsure, run I2C Scanner
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int OBSTACLE_CM  = 20;
const int MAX_DISTANCE = 400;

long distanceMeasure();
void forward(int speedVal);
void backward(int speedVal);
void turnLeft(int speedVal);
void turnRight(int speedVal);
void stopMotors();
long averDistance();
void display(long data);
void smartAvoid();


