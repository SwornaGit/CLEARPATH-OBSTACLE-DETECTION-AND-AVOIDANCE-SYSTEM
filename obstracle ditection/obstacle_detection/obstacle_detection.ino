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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();         // Start I2C communication
  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on backlight

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("LCD Connected!");

  lcd.setCursor(0, 1);
  lcd.print("Leonardo I2C");

  stopMotors();

}

void loop() {
  // put your main code here, to run repeatedly:
  long dist = averDistance();
  int s = digitalRead(IR_PIN);

  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  if (s == LOW){
    delay(400);
    stopMotors();
  }else{
      if (dist > 0 && dist < OBSTACLE_CM) {
      smartAvoid();
    } else {
  display(dist);
  forward(150);
  }
  }



}


void smartAvoid() {
  stopMotors();
  delay(PAUSE_MS);

  // 1) Try RIGHT
  turnRight(SPEED_TURN);
  delay(TURN_TIME_MS);
  stopMotors();
  delay(PAUSE_MS);

  long dRight = averDistance();
  display(dRight);
  delay(100);

  // If right is also blocked, go LEFT twice (net: ends facing left)
  if (dRight > 0 && dRight < OBSTACLE_CM) {
    // turn left for 2x time (right + 2*left => net left)
    turnLeft(SPEED_TURN);
    delay(TURN_TIME_MS * 2);
    stopMotors();
    delay(PAUSE_MS);
  }

  // move forward after choosing direction
  forward(SPEED_MOVE);
}

void display(long data){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Obstacle Detection!");

  lcd.setCursor(0, 1);
  lcd.print(data);
}

// One raw measurement with timeout + clamp
long distanceMeasure() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 20000);  // timeout

  if (duration == 0) {
    return MAX_DISTANCE;              // timeout → treat as very far
  }

  long distance = duration * 0.034 / 2;  // cm

  if (distance > MAX_DISTANCE) {
    distance = MAX_DISTANCE;
  }
  return distance;
}
// Simple smoothing: 3 samples, ignore 400s, average others
long averDistance() {
  const int N = 3;
  long sum = 0;
  int count = 0;

  for (int i = 0; i < N; i++) {
    long d = distanceMeasure();
    if (d > 0 && d < MAX_DISTANCE) {  // ignore 400 (error)
      sum += d;
      count++;
    }
    delay(10);  // small gap between pings
  }
  if (count == 0) {
    return MAX_DISTANCE;  // all were bad
  }
  return sum / count;     // average of valid readings
}

void forward(int speedVal) {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, speedVal);

  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENB_PIN, speedVal);
}

void backward(int speedVal) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, speedVal);

  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENB_PIN, speedVal);
}

