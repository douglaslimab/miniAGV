
//---------------------------------------------------------------
//Project: miniAGV 
//Started: 30/08/2016 21:57       Last Update: 13/01/2021
//Author: Douglas Lima
//Features:  Motor Shield L298P
//           Bluetooth Module
//           Pan/Tilt Servo Camera
//---------------------------------------------------------------

#include <Servo.h>

Servo servo1, servo2;
byte pos = 0;
char comando[2];


//Motor Shield Pins----------------------------------------------
const int dirA = 12;
const int dirB = 13;
const int pwmA = 10;
const int pwmB = 11;
const int brkA = 9;
const int brkB = 8;
const int sns0 = A0;
const int sns1 = A1;

const int speaker = 4;

void setup() {
  Serial.begin(9600);

  servo1.attach(9);
  servo2.attach(10);

  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brkA, OUTPUT);
  pinMode(brkB, OUTPUT);
  pinMode(speaker, OUTPUT);

  pinMode(sns0, INPUT);
  pinMode(sns1, INPUT);

  digitalWrite(brkA, LOW);
  digitalWrite(brkB, LOW);
}

void loop() {
  if (Serial.available()) {
    for (int i = 0; i < 2; i++) {
      comando[i] = Serial.read();
      delay(10);
    }
  }
  pos = comando[1];

  switch (comando[0]) {
    case'a':
      servo1.write(pos);
      break;
    case 'b':
      servo2.write(pos);
      break;
    case 'c':
      if (pos <= 127) {
        analogWrite(pwmA, 255 - pos*2);
        digitalWrite(dirA, HIGH);
      }
      else if (pos > 127) {  
        pos = pos - 127;
        analogWrite(pwmA, pos*2 - 1);
        digitalWrite(dirA, LOW);      
      }
      break;
    case 'd':
      if (pos <= 127) {
        analogWrite(pwmB, 255 - pos*2);
        digitalWrite(dirB, LOW);
      }
      else if (pos > 127) {
        pos = pos - 127;
        analogWrite(pwmB, pos*2 - 1);
        digitalWrite(dirB, HIGH);
      }
      break;
      case 'e':
      comando[0] = 'E';
      buzz(3);
      break;
  }
}

void buzz(int f){
  int i = 0;
  for(i = 0; i < 20; i++){
    digitalWrite(speaker, HIGH);
    delay(f);
    digitalWrite(speaker, LOW);
    delay(f);
  }
}
