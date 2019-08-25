
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo servoLeft;
Servo servoRight;
int trigPin = 5;
int echoPin = 6;
const byte MyAddress[5] = {'R','x','A','D','C'};


RF24 radio(9, 10); //pin 9 and 10 for radio

bool newData = false;
long distance;
long duration;
int input;

void setup() {
  servoLeft.attach(2); 
  servoRight.attach(3);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, MyAddress);
  radio.startListening();
}

void loop(){
  if (radio.available()) {
    Serial.println("--------------------------------");
    radio.read(&input, sizeof(input));
    checkDistance();
    int input2 = input;
    newData = true;
    Serial.println("Data received!!");
    
    Serial.print("COMMAND = ");
    Serial.println(input2);
    
    if (input2 == 1) {
      checkDistance();
      Serial.print("Distance: ");
      Serial.println(distance);
      
      if (distance >= 10) {
        Serial.println("MOVING FORWARD");
        forward();
        delay(50);
      } 
      else if (distance < 10) {
          Serial.println("TURNING");
          stopCar();
          delay(500);
          reverse();
          delay(500);
          turnVehicle();
          delay(500);
          
      }
      delay(500);
    }
  }
  distance = 1000;
}

void forward() {
  servoLeft.write(180);  // move the left motor clockwise
  servoRight.write(0);   // move the right motor counterclockwise
}

void stopCar() {
  servoLeft.write(90);   // stops the left motor
  servoRight.write(90);  // stops the right motor
  delay(500);
}

void turnVehicle() {
    servoLeft.write(90);
    servoRight.write(0);    
  
}

void reverse() {
    servoLeft.write(0);
    servoRight.write(180);    
}

void checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
}
