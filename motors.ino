#include <IRremote.h>
IRsend irsend;

int RECV_PIN = 4;//1
IRrecv irrecv(RECV_PIN);
decode_results results;

int enableA = 5;
int MotorA1 = 6;
int MotorA2 = 7;

int enableB = 8;
int MotorB1 = 9;
int MotorB2 = 10;
int Dword;
int flag = 0; //8 forw 2back 4 left 6right
int flagst = 0;

void setup() {
  Serial.begin (9600);
  irrecv.enableIRIn();
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT);
  Forward (1);
  stop();
}
void en() {
  Serial.print ("En -  ");
  digitalWrite (enableA, HIGH);
  digitalWrite (enableB, HIGH);
}


void stop() {
  Serial.println ("  - St");
  digitalWrite (enableA, LOW);
  digitalWrite (enableB, LOW);
  digitalWrite (MotorA1, LOW);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, LOW);
}

void Forward (int a) {
  Serial.print ("Forward");
  flag = 8;
  digitalWrite (MotorA1, LOW); //A Forward
  digitalWrite (MotorA2, HIGH); //A Forward
  digitalWrite (MotorB1, LOW); //B Forward
  digitalWrite (MotorB2, HIGH);  //B Forward
  en();
  delay (a);
  //  stop();
}

void Backward (int a) {
  flag = 2;
  Serial.print ("backward");
  digitalWrite (MotorA1, HIGH); //A Backward
  digitalWrite (MotorA2, LOW); //A Backward
  digitalWrite (MotorB1,  HIGH); //B Backward
  digitalWrite (MotorB2, LOW); //B Backward
  en();
  delay (a);
  // stop();
}

void left(int a) {
  flag = 4;
  Serial.print ("left");
  digitalWrite (MotorA1, LOW); //A Forward
  digitalWrite (MotorA2, HIGH); //A Forward
  digitalWrite (MotorB1,  HIGH); //B Backward
  digitalWrite (MotorB2, LOW); //B Backward
  en();
  delay (a);
  // stop();
}

void right(int a) {
  flag = 6;
  Serial.print ("right");
  digitalWrite (MotorA1, HIGH); //A Backward
  digitalWrite (MotorA2, LOW); //A Backward
  digitalWrite (MotorB1, LOW); //B Forward
  digitalWrite (MotorB2, HIGH);  //B Forward
  en();
  delay (a);
  // stop();
}
void loop() {


  Dword = Serial.read();

  if (Dword == 'w') {
    Forward (100);
  }
  if (Dword == 's') {
    Backward (100);
  }
  if (Dword == 'a') {
    left(100);
  }
  if (Dword == 'd') {
    right(100);
  }

  if (irrecv.decode(&results)) //this checks to see if a code has been received
  { Serial.println(results.value, HEX);

    if (results.value == 0xFFAA55)  {
      Forward (1); flag = 8;
    }
    if (results.value == 0xFFE01F)  {
      Backward (1); flag = 2;
    }
    if (results.value == 0xFF7A85)  {
      left(1); flag = 4;
    }
    if (results.value == 0xFFA05F)  {
      right(1); flag = 6;
    }
    if (results.value == 0xFF609F)  {
      stop();
    }

 /*    if (results.value == 0xFFFFFFFF)  {
      if (flag == 8) {
        Forward (100);
      }
      if (flag == 2) {
        Backward (1);
      }
      if (flag == 4) {
        left(1);
      }
      if (flag == 6) {
        right(1);
      }
    }*/
    //else {stop();}
    irrecv.resume(); //receive the next value
  }
  delay(100);
}


