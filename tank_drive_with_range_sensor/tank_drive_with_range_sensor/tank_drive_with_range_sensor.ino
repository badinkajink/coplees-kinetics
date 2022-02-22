/*
control relay for vibration motor
@author William Xie
*/
#include <SparkFun_TB6612.h>

#define AIN1 5
#define AIN2 6
#define PWMA 9
#define BIN1 2
#define BIN2 3
#define PWMB 10
#define STBY 8
#define trig 11
#define echo 12

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int dist;
long dur;
int randNumber;
int ctr = 0;
int defaultSpeed = 100;

void setup() {
    Serial.begin(9600);
    
    // setup hc-sr04 range sensor
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    
    // setup tank drive
    // pinMode(AIN1, OUTPUT);
    // pinMode(AIN2, OUTPUT);
    // pinMode(PWMA, OUTPUT);
    // pinMode(BIN1, OUTPUT);
    // pinMode(BIN2, OUTPUT);
    // pinMode(PWMB, OUTPUT);
    // pinMode(STBY, OUTPUT);
}

int getDistance() {
    // clear trigPin condition
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    
    // set trig to HIGH (ACTIVE) for 10 us
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    // read echo travel time in us
    dur = pulseIn(echo, HIGH);
    
    // calculate distance, multiply by speed of sound and divide by 2
    // because wave needs to travel there and back
    dist = dur * 0.034 / 2;
    return dist;
}

void loop() {
  dist = getDistance();
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    int temp = Serial.parseInt();
    if (temp >= 0 && temp <= 255) {
      defaultSpeed = temp;
      // say what you got:
      Serial.print("defaultSpeed set to: ");
      Serial.println(defaultSpeed, DEC);
    }
  }
  
  if (dist < 15)
  {
    motor1.drive(-defaultSpeed,1000);
    motor2.drive(defaultSpeed,1000);
    delay(330);
    forward(motor1, motor2, defaultSpeed);
    delay(300);
  }
  
  randNumber = random(0, 100);
  Serial.print("randNumber: ");
  Serial.println(randNumber, DEC);

  if (randNumber > 75) {
    motor1.drive(-defaultSpeed,1000);
    motor2.drive(defaultSpeed,1000);
    delay(3000);
    forward(motor1, motor2, defaultSpeed);
    delay(1000);
  }
  else if (randNumber > 50) {
    // right
    motor1.drive(defaultSpeed,1000);
    motor2.drive(-defaultSpeed,1000);
    delay(2500);
    forward(motor1, motor2, defaultSpeed);
    delay(1500);
  }
  else if (randNumber > 25) {
    // forward
    forward(motor1, motor2, defaultSpeed);
    delay(4000);
  }
  else {
    // back
    back(motor1, motor2, -1.1*defaultSpeed);
    delay(4000);
  }
  
  delay(1000);

  // motor1.brake();
  // motor2.brake();
  // brake(motor1, motor2);
}
