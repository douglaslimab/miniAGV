// Serial data

int serialPack[4];
byte spd = 0;

// Motor Shield Pins

const int dirA = 12;
const int dirB = 13;
const int pwmA = 10;
const int pwmB = 11;
const int brkA = 9;
const int brkB = 8;
const int sns0 = A0;
const int sns1 = A1;

const int speaker = 4;

void setup(){
  Serial.begin(9600);

  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brkA, OUTPUT);
  pinMode(brkB, OUTPUT);

  pinMode(speaker, OUTPUT);

  digitalWrite(brkA, LOW);
  digitalWrite(brkB, LOW);
}

void loop(){
  if (Serial.available()){
    for(int i = 0; i < 4 ; i++){
      serialPack[i] = Serial.read();
      delay(5);
    }
  }
  spd = 100*(serialPack[1] - '0') + 10*(serialPack[2] - '0') + (serialPack[3] - '0');

  switch (serialPack[0]){
    case'c':
    if (spd <= 127){
      analogWrite(pwmA, 255 - spd*2);
      digitalWrite(dirA, HIGH);
    } else if (spd > 127){
      spd = spd - 127;
      analogWrite(pwmA, spd*2 - 1);
      digitalWrite(dirA, LOW);
    }
    break;
    case'd':
    if (spd <= 127){
      analogWrite(pwmB, 255 - spd*2);
      digitalWrite(dirB, LOW);
    } else if ( spd > 127){
      spd = spd - 127;
      analogWrite(pwmB, spd*2 - 1);
      digitalWrite(dirB, HIGH);
    }
    break;
    case'e':{
      serialPack[0] = 'E';
      analogWrite(pwmA, 0);
      analogWrite(pwmB, 0);
    }
    break;
  }
}
