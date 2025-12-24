#define TRIG_PIN 7
#define ECHO_PIN 6

const int OBSTACLE_CM  = 20;
const int MAX_DISTANCE = 400;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}
