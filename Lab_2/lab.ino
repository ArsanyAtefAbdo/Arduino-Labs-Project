#include <IRremote.h>
#include <IRremoteInt.h>

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

const int LM_pin = A5; // Assigning analog pin A5 to LM35
const int output = 8;    // Assigning analog pin A0 to LED
int IR_pin = 11;       // IR pin
float Celsius;         // variable to store temperature in degree Celsius
float sensorValue;     // temporary variable to hold sensor reading
float threshold;
float currentThreshold;

IRrecv IR_recv(IR_pin);  //receive from IR pin
decode_results results;

/* appending number in string "threshold" */
void append() {
  switch (results.value) {
    case ZERO: threshold = threshold * 10 + 0; Serial.println("0 received"); break;
    case ONE: threshold = threshold * 10 + 1; Serial.println("1 received"); break;
    case TWO: threshold = threshold * 10 + 2; Serial.println("2 received"); break;
    case THREE: threshold = threshold * 10 + 3; Serial.println("3 received"); break;
    case FOUR: threshold = threshold * 10 + 4; Serial.println("4 received"); break;
    case FIVE: threshold = threshold * 10 + 5; Serial.println("5 received"); break;
    case SIX: threshold = threshold * 10 + 6; Serial.println("6 received"); break;
    case SEVEN: threshold = threshold * 10 + 7; Serial.println("7 received"); break;
    case EIGHT: threshold = threshold * 10 + 8; Serial.println("8 received"); break;
    case NINE: threshold = threshold * 10 + 9; Serial.println("9 received"); break;
  }
  return;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LM_pin, INPUT);   // LM_pin is the input temperature
  pinMode(output, OUTPUT);     // Define pins led
  digitalWrite(output, LOW);
  IR_recv.enableIRIn();     //start the receiver
  IR_recv.blink13(true);
  threshold = 0.0;                  //initial the string by null
  currentThreshold = 30.0;
}

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(LM_pin);       // read the input temprature in millivolt
  Celsius = (sensorValue * 500 / 1024);  // convert from millivolt to celsius
  Serial.print("Celsius: ");
  Serial.println(Celsius);

  if (IR_recv.decode(&results)) {
    switch (results.value) {
      case OK: {
          currentThreshold = threshold;
          Serial.print("Threshold: "); Serial.println(currentThreshold);
          threshold = 0;
        } break;
      default: append();
    }
    delay(50);                    // Add delay to prevent false readings
    IR_recv.resume();             // receive the next value
  }

  if (Celsius > currentThreshold) {
    digitalWrite(output, HIGH);
  } else {
    digitalWrite(output, LOW);
  }
  delay(500);
}
