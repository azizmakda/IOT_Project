#include <SPI.h> 
#include <nRF24L01.h>  
#include <RF24.h>

#include <Servo.h>

Servo servoLeft;
Servo servoRight;

const byte ReceiverAddress[5] = {'R','x','A','D','C'};       //address of the receiver 

RF24 radio(9, 10);         // initialize a Radio variable, this module is connected to pins 9 and 10

char dataToSend[10] = "Hello";      //the command/data you need to send to the receiver 
bool newData;
long distance;
long time;

int input = 1;
String command2 = "turn";
int tempNum = 0; //if 0 == comand 1, if 1 == command 2

String start = "start";

void setup() {

  Serial.begin(9600);
  radio.begin();  //begin the radio module     
  radio.setDataRate( RF24_250KBPS );           
  radio.setRetries(3,5);                                     
  radio.openWritingPipe(ReceiverAddress); 
   
}

void loop() {
  Serial.print("Sending instruction: ");     
  Serial.println(input);             
  bool result = radio.write( &input, sizeof(input) );     
  //byte results = radio.write( &input, sizeof (input) ); 

 
  if (result) {
  {         
       Serial.println(" Data sent and an acknowledge is received");       
 
 else {        
       Serial.println(" transmission is failed");     
  }   


}
