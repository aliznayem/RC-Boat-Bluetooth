#include <Servo.h>
#include <SevSeg.h>

Servo port;
Servo starboard;
Servo bldc;
SevSeg speedmeter;
char command = 'S';
int led = 13;
int ledG = 7;
int bldcPin = 12;
int lservo = 11;
int rservo = 10;
int relayA = 9;
int relayB = 8;
int pulseTime = 1100;
int posR = 76;
int posL = 82;
int pspeed = 00;


void setup()
{
  Serial.begin(9600);
  port.attach(lservo);
  starboard.attach(rservo);
  bldc.attach(bldcPin);
  port.write(posL);
  starboard.write(posR);
  pinMode(relayA, OUTPUT);
  pinMode(relayB, OUTPUT);
  delay(1);
  bldc.writeMicroseconds(1000); //bldc arming

  byte numDigits = 2; //speed display digits
  byte digitPins[] = {38, 40}; //A,B,C,D,E,F,G pin
  byte segmentPins[] = {36, 34, 32, 30, 28, 26, 24}; //digit-1 cathode, digit-2 cathode
  speedmeter.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  pinMode(led, OUTPUT);
  pinMode(ledG, OUTPUT);
  digitalWrite(led, HIGH);
  digitalWrite(ledG, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    if (command == 'F') {    //move front
      digitalWrite(relayA, LOW);
      digitalWrite(relayB, LOW);
      posL = 82;
      posR = 76;
      port.write(posL);       //left servo
      starboard.write(posR);  //right servo
      bldc.writeMicroseconds(pulseTime);
    }
    else if (command == 'B') {    //move back
      digitalWrite(relayA, HIGH);
      digitalWrite(relayB, HIGH);
      posL = 82;
      posR = 76;
      port.write(posL);       //left servo
      starboard.write(posR);  //right servo
      bldc.writeMicroseconds(pulseTime);
    }
    else if (command == 'L') {   //move left, motor off
      posR += 5;
      posL += 5;
      if (posR > 116)
        posR = 116;
      if (posL > 122)
        posL = 122;
      starboard.write(posR);
      port.write(posL);
    }
    else if (command == 'R') {     //move right, motor off
      posR -= 5;
      posL -= 5;
      if (posR < 36)
        posR = 36;
      if (posL < 42)
        posL = 42;
      starboard.write(posR);
      port.write(posL);
    }
    else if (command == 'S') {    //default
      digitalWrite(relayA, LOW);
      digitalWrite(relayB, LOW);
      posR = 76;
      posL = 82;
      starboard.write(posR);
      port.write(posL);
      bldc.writeMicroseconds(1000);
    }
    else if (command == 'I') {    //move right, motor on
      digitalWrite(relayA, LOW);
      digitalWrite(relayB, LOW);
      bldc.writeMicroseconds(pulseTime);
      posR -= 5;
      posL -= 5;
      if (posR < 36)
        posR = 36;
      if (posL < 42)
        posL = 42;
      starboard.write(posR);
      port.write(posL);
    }
    else if (command == 'J') {    //move back-right
      digitalWrite(relayA, HIGH);
      digitalWrite(relayB, HIGH);
      bldc.writeMicroseconds(pulseTime);
      posR -= 5;
      posL -= 5;
      if (posR < 36)
        posR = 36;
      if (posL < 42)
        posL = 42;
      starboard.write(posR);
      port.write(posL);
    }
    else if (command == 'G') {    //move left, motor on
      digitalWrite(relayA, LOW);
      digitalWrite(relayB, LOW);
      bldc.writeMicroseconds(pulseTime);
      posR += 5;
      posL += 5;
      if (posR > 116)
        posR = 116;
      if (posL > 122)
        posL = 122;
      starboard.write(posR);
      port.write(posL);
    }
    else if (command == 'H') {    //move back-left
      digitalWrite(relayA, HIGH);
      digitalWrite(relayB, HIGH);
      bldc.writeMicroseconds(pulseTime);
      posR += 5;
      posL += 5;
      if (posR > 116)
        posR = 116;
      if (posL > 122)
        posL = 122 ;
      starboard.write(posR);
      port.write(posL);
    }
    //set speed
    else if (command == '0') {
      pulseTime = 1100;
      pspeed = 00;
    }
    else if (command == '1') {
      pulseTime = 1190;
      pspeed = 10;
    }
    else if (command == '2') {
      pulseTime = 1200;
      pspeed = 20;
    }
    else if (command == '3') {
      pulseTime = 1225;
      pspeed = 30;
    }
    else if (command == '4') {
      pulseTime = 1250;
      pspeed = 40;
    }
    else if (command == '5') {
      pulseTime = 1275;
      pspeed = 50;
    }
    else if (command == '6') {
      pulseTime = 1300;
      pspeed = 60;
    }
    else if (command == '7') {
      pulseTime = 1400;
      pspeed = 70;
    }
    else if (command == '8') {
      pulseTime = 1500;
      pspeed = 80;
    }
    else if (command == '9') {
      pulseTime = 1700;
      pspeed = 90;
    }
    else if (command == 'q') {
      pulseTime = 1800 ;
      pspeed = 99;
    }
  }
  speedmeter.refreshDisplay();
  speedmeter.setNumber(pspeed, 2);
}

