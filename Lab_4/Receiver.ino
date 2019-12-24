#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(7, 8); // CE, CSN

const int MORSE = 10;
const byte address[6] = "00001";

String alphapet[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
                       ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                       "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
String numbers[10] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
int unit_time = 500;
String input = "";
int val = 0;
 
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  digitalWrite(MORSE, LOW);
  
}

void dot () {  
  digitalWrite(MORSE, HIGH);
  Serial.print (".");
  Serial.print ("1");
  delay(unit_time);
  digitalWrite(MORSE, LOW);
}

void dash () {
  digitalWrite(MORSE, HIGH);
  Serial.print ("-");
  Serial.print ("3");
  delay(3*unit_time);
  digitalWrite(MORSE, LOW);
}

void interelement_gap () {
  digitalWrite(MORSE, LOW);
  Serial.print ("(1)");
  delay(unit_time);
}

void short_gap () {
  digitalWrite(MORSE, LOW);
  Serial.print (" (3) ");
  delay(3*unit_time);
}

void medium_gap () {
  digitalWrite(MORSE, LOW);
  Serial.println();
  Serial.print ("(7)");
  Serial.println();
  delay(7*unit_time);
}

void to_morse (String in) {
  //Serial.println(in);
  int sent_length = in.length();
  for (int i = 0; i < sent_length; i++) {
    String code = "";
    if (in[i] >= '0' && in[i] <= '9') {
      code = numbers[in[i] - '0'];
      
    } else if (in[i] >= 'A' && in[i] <= 'Z') {
      code = alphapet[in[i] - 'A'];
      
    } else if (in[i] == ' ') {
      medium_gap ();

    } else {
      return;
    }

    int code_length = code.length();
    for (int j = 0; j < code_length; j++) {
      if (code[j] == '.') {
        dot();
      } else {
        dash();
      }
      if(j != code_length - 1){
        interelement_gap();
      }
    }
    if(i != sent_length - 2 && in[i] != ' ' && in[i+1] != ' '){
      short_gap();
    }
  }
}
void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    char message[32] = "";
    radio.read(&message, sizeof(message));
    String s(message);
    input = s;
    
    if (input != "") {
      Serial.println("\n\n"+input);
      to_morse (input);
    }  
  }
    
}
