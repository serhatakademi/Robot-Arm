#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//SCK -> 13//MISO -> 12//MOSI -> 11
#define CE_PIN 8
#define CSN_PIN 7

RF24 radio(CE_PIN, CSN_PIN);

const uint64_t pipe = 0xE8E8F0F0E1LL;

int veri[6]; 

void setup() {
  pinMode(potx1,INPUT);
  pinMode(poty1,INPUT);
  pinMode(potx2,INPUT);
  pinMode(poty2,INPUT);
  pinMode(butonPin1, INPUT_PULLUP);
  pinMode(butonPin2, INPUT_PULLUP);
  Serial.begin(9600); // seri iletişimi açtık
  radio.begin(); // radio iletişimi açtık
  radio.openWritingPipe(pipe);
}

void loop() { 
  veri[0] = digitalRead(butonPin1);
  veri[1] =analogRead(potx1);
  veri[2] =analogRead(poty1);
  veri[3] = digitalRead(butonPin2);
  veri[4] =analogRead(potx2);
  veri[5] =analogRead(poty2);
  radio.write( veri, sizeof(veri) ); // bu verileri alıcıya data adında ilet

}
