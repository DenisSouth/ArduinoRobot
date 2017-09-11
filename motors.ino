#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long eventTime = 0;
int timer = 12;

int L13 = 13;
int enableA = 5;
int MotorA1 = 6;
int MotorA2 = 7;
int enableB = 8;
int MotorB1 = 9;
int MotorB2 = 10;

void setup() {
  Serial.begin (9600);
  irrecv.enableIRIn();
  pinMode(timer, OUTPUT); pinMode(L13, OUTPUT); pinMode (enableA, OUTPUT); pinMode (MotorA1, OUTPUT); pinMode (MotorA2, OUTPUT); pinMode (enableB, OUTPUT); pinMode (MotorB1, OUTPUT); pinMode (MotorB2, OUTPUT);
  digitalWrite(timer, LOW) , digitalWrite(L13, LOW);
  Forward ();
  Stop();
}
void en() {
  digitalWrite (enableA, HIGH);
  digitalWrite (enableB, HIGH);
}
void Stop() {
  digitalWrite (enableA, LOW);
  digitalWrite (enableB, LOW);
  digitalWrite (MotorA1, LOW);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, LOW);
}
void Forward () {
  digitalWrite (MotorA1, LOW);
  digitalWrite (MotorA2, HIGH);
  digitalWrite (MotorB1, LOW );
  digitalWrite (MotorB2, HIGH);
  en();
}
void Backward () {
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
  en();
}
void Right() {
  digitalWrite (MotorA1, LOW);
  digitalWrite (MotorA2, HIGH);
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
  en();
}
void Left() {
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, HIGH);
  en();
}

void loop() {
  if (digitalRead(RECV_PIN) == LOW)     eventTime = millis(), digitalWrite(timer, HIGH);
  if (millis() - eventTime > 100) digitalWrite(timer, LOW),

    digitalWrite(L13, LOW), Stop(), Serial.println("Stop");
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFAA55 && (digitalRead(timer) == HIGH) ) {
      Forward ();
    }
    if (results.value == 0xFFE01F && (digitalRead(timer) == HIGH) ) {
      Backward ();
    }
    if (results.value == 0xFF7A85 && (digitalRead(timer) == HIGH) ) {
      Left();
    }
    if (results.value == 0xFFA05F && (digitalRead(timer) == HIGH) ) {
      Right();
    }
    irrecv.resume();
  }
}
