#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
String input;

char text[32];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(1000);
    if (Serial.available()){  
    input = Serial.readString();
    input.toCharArray(text, 32);
    input = "";
    Serial.println(text);
    radio.write(&text, sizeof(text));
    delay(1000);
  }
}
