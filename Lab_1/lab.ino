#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>

#define ZERO 0xFF906F
#define ONE 0xFF30CF
#define TWO 0xFFB04F
#define THREE 0xFF708F
#define FOUR 0xFFF00F
#define FIVE 0xFF08F7
#define SIX 0xFF8877
#define SEVEN 0xFF48B7
#define EIGHT 0xFFC837
#define NINE 0xFF28D7
#define OK 0xFFC03F
#define DOWN 0xFFE01F
#define UP 0xFF10EF

int IR_pin = 11;    // IR pin
int servo_pin = 6; // Servo bin
uint64_t pos;
Servo servo;       //servo object

IRrecv IR_recv(IR_pin);  //receive from IR pin
decode_results results;

/* appending number in string "pos" */
void append() {
  switch (results.value) {
    case ZERO: pos = pos * 10 + 0; Serial.println("0 received"); break;
    case ONE: pos = pos * 10 + 1; Serial.println("1 received"); break;
    case TWO: pos = pos * 10 + 2; Serial.println("2 received"); break;
    case THREE: pos = pos * 10 + 3; Serial.println("3 received"); break;
    case FOUR: pos = pos * 10 + 4; Serial.println("4 received"); break;
    case FIVE: pos = pos * 10 + 5; Serial.println("5 received"); break;
    case SIX: pos = pos * 10 + 6; Serial.println("6 received"); break;
    case SEVEN: pos = pos * 10 + 7; Serial.println("7 received"); break;
    case EIGHT: pos = pos * 10 + 8; Serial.println("8 received"); break;
    case NINE: pos = pos * 10 + 9; Serial.println("9 received"); break;
  }
  return;
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  servo.attach(servo_pin);    //Attach the Servo variable to apin
  servo.write(0);             //write in the number entered to IR

  IR_recv.enableIRIn();       //start the receiver
  IR_recv.blink13(true);
  pos = 0;                   //initial the string by null
}

void loop() {
  // put your main code here, to run repeatedly:

  /* check "results" is found or not */
  if (IR_recv.decode(&results)) {
    // Serial.println(results.value, HEX);

    /* check the "results.value" if (OK - UP - Down - NUMBER) */
    switch (results.value) {
      case OK: {
          if (pos > 180) {
            pos = pos % 180;
          }
          servo.write(pos);
          Serial.println("current angle= " + String(servo.read()));
          pos = 0;
        } break;
      case UP:
        if (servo.read() == 180) {
          servo.write(180);
        } else if (servo.read() < 180) {
          servo.write((servo.read() + 10));
          Serial.println("+10 received"); Serial.println("current angle= " + String(servo.read()));
        } break;
      case DOWN:
        if (servo.read() > 0) {
          servo.write((servo.read() - 10));
          Serial.println("-10 received"); Serial.println("current angle= " + String(servo.read()));
        } break;
      default: append();
    }
    // Add delay to prevent false readings
    delay(50);
    //receive the next value
    IR_recv.resume();
  }
}
