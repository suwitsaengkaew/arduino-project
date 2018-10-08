const int enb = 6; // PWM pin 6
const int in3 = 7;
const int in4 = 8;
const int in10 = 10;
const int in11 = 2;
void setup() {
  pinMode(in10, OUTPUT);
  pinMode(in11, OUTPUT);
  digitalWrite(in11, HIGH);
//  pinMode(in3, OUTPUT);
//  pinMode(in4, OUTPUT);
//  pinMode(enb, OUTPUT);
}
void slow() {
  analogWrite(enb, 128);
}
void fast() {
  analogWrite(enb, 255);
}

void turnleft() {
  //digitalWrite(in10, 0);
  digitalWrite(in11, HIGH);
  delay(10000);
  digitalWrite(in11, LOW);
}

void turnright() {
  
}

void loop() {

  //turnleft();
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, HIGH);
  //slow();
  //delay(1000);
  //fast();
  //delay(1000);
  // change of direction
  //digitalWrite(in3, HIGH);
  //digitalWrite(in4, LOW);
  //slow();
  //delay(1000);
  //fast();
  //delay(1000);
}
