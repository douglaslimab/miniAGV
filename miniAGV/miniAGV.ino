
//---------------------------------------------------------------
//Descrição: Programa de Teste 
//Data: 30/08/2016 21:57        Última Atualização: 30/08/2016
//Autor: Douglas Lima
//Comentários:  Teste da Ponte H L298
//              Teste com Módulo Bluetooth
//              Teste com Suporte Pan/Tilt para Câmera
//---------------------------------------------------------------

#include <Servo.h>

Servo servo1, servo2;
byte pos = 90;
char comando[3];


//Motor Shield Pins-------------------------------------
const int dirA = 12;
const int dirB = 13;
const int pwmA = 10;
const int pwmB = 11;
const int brkA = 9;
const int brkB = 8;
const int sns0 = A0;
const int sns1 = A1;

const int speaker = 4;
 
int rele1 = 22;
int rele2 = 23;
int rele3 = 24;
int rele4 = 25;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

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
  
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);
  digitalWrite(rele4, HIGH);
}

void loop() {
  if (Serial1.available()) {
    for (int i = 0; i < 3; i++) {
      comando[i] = Serial1.read();
      delay(10);
    }
  }
  pos = comando[0];

  switch (comando[1]) {
    case 'a':
      servo1.write(pos);
      break;
    case 'b':
      servo2.write(pos);
      break;
    case 'c':
      if (pos <= 127) {
//        analogWrite(pwmA, 255 - pos*2);
        analogWrite(pwmA, pos);
        digitalWrite(dirA, HIGH);
        Serial.print("Motor A: ");
        Serial.println(pos);
      }
      else if (pos > 127) {
        pos = pos - 127;
//        analogWrite(pwmA, pos*2 - 1);
        analogWrite(pwmA, pos);
        digitalWrite(dirA, LOW);
        Serial.print("Motor B: ");
        Serial.println(pos);
      }
      break;
    case 'd':
      if (pos <= 127) {
//        analogWrite(pwmB, 255 - pos*2);
        analogWrite(pwmB, pos);
        digitalWrite(dirB, HIGH);
        Serial.print("Motor A: ");
        Serial.println(pos);
      }
      else if (pos > 127) {
        pos = pos - 127;
//        analogWrite(pwmB, pos*2 - 1);
        analogWrite(pwmB, pos);
        digitalWrite(dirB, LOW);
        Serial.print("Motor B: ");
        Serial.println(pos);
      }
      break;
  }
}
