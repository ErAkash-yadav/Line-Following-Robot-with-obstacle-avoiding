#include <AFMotor.h>
#include <Servo.h>

// Motors
AF_DCMotor rightMotor(1);
AF_DCMotor leftMotor(2);

// IR Sensors
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4

// Ultrasonic Sensor Pins
#define trigPin A5
#define echoPin 10

// Servo
#define servoPin 9
Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(90); // Center position

  rightMotor.setSpeed(100);
  leftMotor.setSpeed(100);
}

void loop() {
  int s1 = digitalRead(ir1);
  int s2 = digitalRead(ir2);
  int s3 = digitalRead(ir3);
  int s4 = digitalRead(ir4);
  int s5 = digitalRead(ir5);

  long distance = scanObstacle();

  if(distance > 0 && distance < 15) {
    stopMotors();
    avoidObstacle();
  } 
  else {
    // Line following logic
    bool onLine = (s1==0 || s2==0 || s3==0 || s4==0 || s5==0);
    if(onLine) {
      if((s1==1)&&(s2==1)&&(s3==0)&&(s4==1)&&(s5==1)) forward();
      else if((s1==1)&&(s2==0)&&(s3==1)&&(s4==1)&&(s5==1)) right();
      else if((s1==0)&&(s2==1)&&(s3==1)&&(s4==1)&&(s5==1)) sharpRight();
      else if((s1==1)&&(s2==1)&&(s3==1)&&(s4==0)&&(s5==1)) left();
      else if((s1==1)&&(s2==1)&&(s3==1)&&(s4==1)&&(s5==0)) sharpLeft();
      else if((s1==0)&&(s2==0)&&(s3==0)&&(s4==0)&&(s5==0)) stopMotors();
      else forward();
    } else {
      stopMotors();
    }
  }

  delay(10);
}

// Motor control functions
void forward() {
  rightMotor.setSpeed(100); leftMotor.setSpeed(100);
  rightMotor.run(FORWARD); leftMotor.run(FORWARD);
}

void backward() {
  rightMotor.setSpeed(100); leftMotor.setSpeed(100);
  rightMotor.run(BACKWARD); leftMotor.run(BACKWARD);
}

void left() {
  rightMotor.setSpeed(130); leftMotor.setSpeed(80);
  rightMotor.run(FORWARD); leftMotor.run(RELEASE);
}

void right() {
  rightMotor.setSpeed(80); leftMotor.setSpeed(130);
  rightMotor.run(RELEASE); leftMotor.run(FORWARD);
}

void sharpLeft() {
  rightMotor.setSpeed(100); leftMotor.setSpeed(100);
  rightMotor.run(FORWARD); leftMotor.run(BACKWARD);
}

void sharpRight() {
  rightMotor.setSpeed(100); leftMotor.setSpeed(100);
  rightMotor.run(BACKWARD); leftMotor.run(FORWARD);
}

void stopMotors() {
  rightMotor.run(RELEASE); leftMotor.run(RELEASE);
}

// Scan obstacle with servo
long scanObstacle() {
  long dCenter = getDistanceAtAngle(90);
  long dLeft = getDistanceAtAngle(45);
  long dRight = getDistanceAtAngle(135);

  // Return the minimum distance detected
  long minDistance = min(dCenter, min(dLeft, dRight));
  return minDistance;
}

// Move servo and get distance
long getDistanceAtAngle(int angle) {
  myServo.write(angle);
  delay(200); // Wait for servo to reach
  long distance = getDistance();
  return distance;
}

// Ultrasonic distance function
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Obstacle avoidance routine
void avoidObstacle() {
  backward();
  delay(400);

  // Check left vs right
  long dLeft = getDistanceAtAngle(45);
  long dRight = getDistanceAtAngle(135);

  if(dLeft > dRight) {
    sharpLeft();
  } else {
    sharpRight();
  }
  delay(400);

  myServo.write(90); // Reset servo center
}