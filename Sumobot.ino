const int trigPin = 2;  // Ultrasonic sensor trig pin
const int echoPin = 3;  // Ultrasonic sensor echo pin
const int motor1pin1 = 4;  // Motor 1 pin 1
const int motor1pin2 = 5;  // Motor 1 pin 2
const int motor1enable = 6;  // Motor 1 enable pin
const int motor2pin1 = 7;  // Motor 2 pin 1
const int motor2pin2 = 8;  // Motor 2 pin 2
const int motor2enable = 9;  // Motor 2 enable pin
const int irLeftPin = 10;
const int irRightPin = 11;
const int buzzerPin = 12;  // Add a buzzer pin

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1enable, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor2enable, OUTPUT);
  pinMode(irLeftPin, INPUT);
  pinMode(irRightPin, INPUT);
  pinMode(buzzerPin, OUTPUT);  // Initialize buzzer pin as output

  // Beating buzzer for 5 seconds
  for (int i = 0; i < 5; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(400);
  }
}

void loop() {
  int distance = getDistance();

  if (distance > 30) {  // If no object is detected by ultrasonic sensor
    // Only use IR sensors to control the motors
    int irLeftState = digitalRead(irLeftPin);
    int irRightState = digitalRead(irRightPin);

    if (irLeftState == LOW && irRightState == HIGH) {  // If left infrared sensor detects a black line
      // Reverse right wheel
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
    } else if (irLeftState == HIGH && irRightState == LOW) {  // If right infrared sensor detects a black line
      // Reverse left wheel
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
    } else if (irLeftState == LOW && irRightState == LOW) {  // If right infrared sensor detects a black line
      // Reverse left wheel
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
    } else {
      // Forward motor direction
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
    }

    // Set motor speed to half maximum
    analogWrite(motor1enable, 100);
    analogWrite(motor2enable, 100);
  } else {
    // Object detected by ultrasonic sensor, use both ultrasonic and IR sensors
    int speed;

    if (distance <= 10) {  // If object is very close
      speed = 255;  // Set motor speed to maximum
    } else {
      speed = 115;  // Set motor speed to half maximum
    }

    int irLeftState = digitalRead(irLeftPin);
    int irRightState = digitalRead(irRightPin);

    if (irLeftState == LOW && irRightState == HIGH) {  // If left infrared sensor detects a black line
      // Reverse right wheel
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
    } else if (irLeftState == HIGH && irRightState == LOW) {  // If right infrared sensor detects a black line
      // Reverse left wheel
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
    } else if (irLeftState == LOW && irRightState == LOW) {  // If right infrared sensor detects a black line
      // Reverse left wheel
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
    } else {
      // Forward motor direction
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
    }

    // Set motor speed
    analogWrite(motor1enable, speed);
    analogWrite(motor2enable, speed);
  }

  delay(50);  // Update motor speed every 50ms
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}