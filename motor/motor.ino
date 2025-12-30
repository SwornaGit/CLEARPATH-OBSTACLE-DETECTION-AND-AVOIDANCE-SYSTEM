// ---------------------------
// Motor A (Left Motor)
#define ENA_PIN 13   // PWM
#define IN1_PIN 10
#define IN2_PIN 8

// Motor B (Right Motor)
#define ENB_PIN 3    // PWM
#define IN3_PIN 4
#define IN4_PIN 5
// ---------------------------

void setup() {
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  stopMotors();   // make sure motors are off at start
}

void loop() {
  forward(150);
  delay(2000);

  backward(150);
  delay(2000);

  turnLeft(150);
  delay(1500);

  turnRight(150);
  delay(1500);

  stopMotors();      
  delay(2000);
}

// ---------------------------
// Motor Control Functions
// ---------------------------

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

void turnLeft(int speedVal) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, speedVal);

  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENB_PIN, speedVal);
}

void turnRight(int speedVal) {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, speedVal);

  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENB_PIN, speedVal);
}

void stopMotors() {
  analogWrite(ENA_PIN, 0);
  analogWrite(ENB_PIN, 0);

  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}
