#include <Servo.h>
#include <SevSeg.h>

Servo port;
Servo starboard;
Servo bldc;
SevSeg speedmeter;
char command = 'S';
int rservo = 12;
int lservo = 11;
int bldc = 10;
int relayA = 9;
int relayB = 8;
int pulseTime = 1100;
int posR = 80;
int posL = 88;


void setup()
{
  Serial.begin(9600);
  port.attach(lservo);
  starboard.attach(rservo);
  bldc.attach(bldc);
  port.write(posL);
  starboard.write(posR);
  pinMode(bldc, OUTPUT);
  pinMode(relayA, OUTPUT);
  pinMode(relayB, OUTPUT);
  bldc.writeMicroseconds(1100); //bldc arming
  
  byte numDigits = 2; //speed display digits  
  byte digitPins[] = {};
  byte segmentPins[] = {};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    if (command == 'F') {
      digitalWrite(relayA, LOW);
      digitalWrite(relayB, LOW);
      posL=88;
      posR=80;
      port.write(posL);       //left servo
      starboard.write(posR);  //right servo
      delay(100);
      bldc.writeMicroseconds(pulseTime);
    }
    else if (command == 'B') {
      digitalWrite(relayA, HIGH);
      digitalWrite(relayB, HIGH);
      delay(10);
      if(pulseTime!=1201){
        bldc.writeMicroseconds(1000);
        delay(50);
        pulseTime= 1201;
      }
      bldc.writeMicroseconds(pulseTime);
        
    }
    else if (command == 'L') {
      posR += 5;
      posL += 5;
      if (posR > 130)
        posR = 130;
      if (posL > 130)
        posL = 130;
      starboard.write(posR);
      port.write(posL);
      delay(50);
    }
    else if (command == 'R') {
      posR -= 5;
      posL -= 5;
      if (posR < 50)
        posR = 50;
      if (posL < 50)
        posL = 50;
      starboard.write(posR);
      port.write(posL);
      delay(50);
    }
    else if (command == 'S') {
      digitalWrite(relayA, LOW);
      digitalWrite(relayB, LOW);
      posR = 80;
      posL = 88;
      starboard.write(posR);
      port.write(posL);
      delay(10);
      bldc.writeMicroseconds(1000);
    }
    else if (command == 'I') {
      bldc.writeMicroseconds(pulseTime);
      posR -= 5;
      posL -= 5;
      if (posR < 50)
        posR = 50;
      if (posL < 50)
        posL = 50;
      starboard.write(posR);
      port.write(posL);
      delay(50);
    }
    else if (command == 'J') {
      digitalWrite(relayA, HIGH);
      digitalWrite(relayB, HIGH);
      delay(10);
      if(pulseTime!=1201){
        bldc.writeMicroseconds(1000);
        delay(50);
        pulseTime= 1201;
      }
      bldc.writeMicroseconds(pulseTime);
      posR -= 5;
      posL -= 5;
      if (posR < 50)
        posR = 50;
      if (posL < 50)
        posL = 50;
      starboard.write(posR);
      port.write(posL);
      delay(50);

    }
    else if (command == 'G') {
      esc(pulseTime);
      posR += 5;
      posL += 5;
      if (posR > 130)
        posR = 130;
      if (posL > 130)
        posL = 130;
      starboard.write(posR);
      port.write(posL);
      delay(50);
    }
    else if (command == 'H') {
      digitalWrite(relayA, HIGH);
      digitalWrite(relayB, HIGH);
      delay(10);
      if(pulseTime!=1201){
        bldc.writeMicroseconds(1000);
        delay(50);
        pulseTime= 1201;
      }
      bldc.writeMicroseconds(pulseTime);
      posR += 5;
      posL += 5;
      if (posR > 130)
        posR = 130;
      if (posL > 130)
        posL = 130;
      starboard.write(posR);
      port.write(posL);
      delay(50);
    }
    else if (command == '0') {
      pulseTime = 1100;
      speedmeter.setNumber(00,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '1') {
      pulseTime = 1170;
      speedmeter.setNumber(10,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '2') {
      pulseTime = 1200;
      speedmeter.setNumber(20,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '3') {
      pulseTime = 1300;
      speedmeter.setNumber(30,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '4') {
      pulseTime = 1400;
      speedmeter.setNumber(40,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '5') {
      pulseTime = 1500;
      speedmeter.setNumber(50,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '6') {
      pulseTime = 1600;
      speedmeter.setNumber(60,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '7') {
      pulseTime = 1700;
      speedmeter.setNumber(70,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '8') {
      pulseTime = 1800;
      speedmeter.setNumber(80,0);
      speedmeter.refreshDisplay();
    }
    else if (command == '9') {
      pulseTime = 1900;
      speedmeter.setNumber(90,0);
      speedmeter.refreshDisplay();
    }
    else if (command == 'q') {
      pulseTime = 2000;
      speedmeter.setNumber(99,0);
      speedmeter.refreshDisplay();
    }

  }
}

