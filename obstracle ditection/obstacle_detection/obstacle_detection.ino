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
