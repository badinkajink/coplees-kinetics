/*
control relay for vibration motor
@author William Xie
*/

int relay1 = 4;
int avg = 0;
int count = 0;

void setup() {
    Serial.begin(9600);
    pinMode(relay1, OUTPUT);
    digitalWrite(relay1, HIGH);
}

void loop() {
    int sound = analogRead(A0);
    Serial.println(sound);
    if (sound > 100)
    {
      digitalWrite(relay1, LOW);
      Serial.println("On");
      delay(3000);
      digitalWrite(relay1, HIGH);
      Serial.println("Off");
    }
    delay(100);
}
