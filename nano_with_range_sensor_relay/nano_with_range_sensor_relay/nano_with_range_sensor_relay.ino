/*
control relay for vibration motor
@author William Xie
*/
int relay1 = 4;
int trig = 11;
int echo = 10;
int dist;
long dur;

void setup() {
    Serial.begin(9600);
    pinMode(relay1, OUTPUT);
    digitalWrite(relay1, HIGH);
    
    // setup hc-sr04 range sensor
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void loop() {
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
    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.println(" cm");
  
    if (dist < 50)
    {
      digitalWrite(relay1, HIGH);
      Serial.println("On");
      delay(180000);
      digitalWrite(relay1, LOW);
      Serial.println("Off");
      delay(10000);
    }
}
