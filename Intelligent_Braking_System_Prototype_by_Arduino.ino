int echo = 11;
int trig = 12;
int enA = 3;
int enB = 6;
int in1 = 2;
int in2 = 4;
int in3 = 7;
int in4 = 8;
int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(LED,OUTPUT);


}

void loop() {
  // Measure the distance using ultrasonic sensor
  float distance = measureDistance();

  // Print the measured distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control motors based on distance thresholds
  if (distance > 25.0) {
    controlMotors(255, 255); // Full speed (255 is the maximum speed)
  } else if (distance <= 25.0 && distance > 15.0) {
    controlMotors(192, 192); // 3/4 of max speed 
  } else if (distance <= 15.0 && distance > 10.0) {
    controlMotors(128, 128); // Half of max speed 
  } else {
    // If distance is less than or equal to 10.0 cm, stop the motors
    stopMotors();
    if (distance < 6.0){
    digitalWrite(LED,HIGH);
    delay(80);
    digitalWrite(LED,LOW);
  }
  }

  delay(100); // Adjust delay as needed for smoother motor control
}

// Function to measure distance using ultrasonic sensor
float measureDistance() {
  const float speedOfSound = 0.0343; // Speed of sound in cm/microsecond

  // Trigger the ultrasonic sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);
  float distance = (duration * speedOfSound) / 2.0; 

  return distance;
}

// Function to control motor speeds
void controlMotors(int speedA, int speedB) {
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);

  // Control the motor direction by setting appropriate input pins
  // Adjust as needed based on your motor wiring configuration
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to stop the motors
void stopMotors() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}


