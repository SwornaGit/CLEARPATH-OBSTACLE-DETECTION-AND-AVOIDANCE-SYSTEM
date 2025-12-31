#define IR_PIN 5   // IR sensor OUT -> D4 (Leonardo)

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
}

void loop() {
  int s = digitalRead(IR_PIN);

  // Many IR modules are ACTIVE-LOW.
  // If it works opposite for you, swap HIGH/LOW in the if.
  Serial.println(s);
  if (s == LOW) {
    Serial.println("WHITE detected -> STOP");
    // stopMotors();
  } else {
    Serial.println("NOT white -> MOVE");
    // forward(150);
  }

  delay(50);
}
