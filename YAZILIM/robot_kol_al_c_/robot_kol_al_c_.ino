int joybut1 = 0;
int joyx1;
int joyy1;
int joybut2 = 0;
int joyx2;
int joyy2;
int pos = 30;
int pose = 30;
#include <Servo.h>
Servo myservo;
Servo myservo1;
#include <Stepper.h>
#define STEPS 200
Stepper stepper1(STEPS, 2, 5);
Stepper stepper2(STEPS, 3, 6);
Stepper stepper3(STEPS, 4, 7);
#define motorInterfaceType 1
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//SCK -> 52//MISO -> 50//MOSI -> 51
#define CE_PIN 49
#define CSN_PIN 53

RF24 radio(CE_PIN, CSN_PIN);

const uint64_t pipe = 0xE8E8F0F0E1LL;
int veri[] = {joybut1, joyx1, joyy1, joybut2, joyx2, joyy2} ;

void setup() {
  // stepper.setSpeed(60);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  myservo.attach(12);
  myservo1.attach(13);
}
void loop() {


  if ( radio.available() )
  {

    radio.read( veri, sizeof(veri) );
    Serial.print("veri[1]");
    Serial.println(veri[2]);
  
    if (veri[1] >= 700) {
      stepper1.setSpeed(500);
      stepper1.step(200);
    }
    else if (veri[1] <= 400) {
      stepper1.setSpeed(500);
      stepper1.step(-200);
    }

    else if (veri[5] <= 400) {
      stepper2.setSpeed(500);
      stepper2.step(200);
    }
    else if (veri[5] >= 700) {
      stepper2.setSpeed(500);
      stepper2.step(-200);
    }

    else if (veri[4] <= 400) {
      stepper3.setSpeed(500);
      stepper3.step(200);
    }
    else if (veri[4] >= 700) {
      stepper3.setSpeed(500);
      stepper3.step(-200);
    }
     else if(veri[2]>=700){
      pos+=1;
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(10);
    }
   
    else if(veri[2]<=400){
      pos-=1;
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(10);
    }
   
   
 else if( veri[3]== LOW){
      pose+=1;
      myservo1.write(pose);              // tell servo to go to position in variable 'pos' 
      delay(10);
        }
  
    else if(veri[0] == LOW){
      pose-=1;
      myservo1.write(pose);              // tell servo to go to position in variable 'pos' 
      delay(10);
    }
  }
}
