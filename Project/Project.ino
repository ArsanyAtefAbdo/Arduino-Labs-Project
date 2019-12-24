#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal.h>

/* remote code */
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

/* LCD */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
//int Contrast = 75;
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/* LM35 */
const int LM_pin = A5; // Assigning analog pin A5 to LM35
float Celsius;         // variable to store temperature in degree Celsius
float sensorValue;     // temporary variable to hold sensor reading
float threshold;
float currentThreshold;
const int LMOUTPUT = A3;

/* IR */
int IR_pin = 3;       // IR pin
IRrecv IR_recv(IR_pin);  //receive from IR pin
decode_results results;

/* servo and ultrasonic */
const int servopin = 2;
const int trigPin = 12;
const int echoPin = 11;
long duration;
int distinCM;
Servo radarServo;

/* flame sensor */
int flame_sensor_pin = 0 ;// initializing pin 0 as the sensor output pin
int flame_pin = HIGH ; // state of sensor
const int flameoutput = A0;

/* appending number in string "threshold" */
void append() {
  lcd.setCursor(1, 0);
  lcd.print("                ");
  lcd.setCursor(1, 0);
  switch (results.value) {
    case ZERO: threshold = threshold * 10 + 0; lcd.print("0 received"); break;
    case ONE: threshold = threshold * 10 + 1; lcd.print("1 received"); break;
    case TWO: threshold = threshold * 10 + 2; lcd.print("2 received"); break;
    case THREE: threshold = threshold * 10 + 3; lcd.print("3 received"); break;
    case FOUR: threshold = threshold * 10 + 4; lcd.print("4 received"); break;
    case FIVE: threshold = threshold * 10 + 5; lcd.print("5 received"); break;
    case SIX: threshold = threshold * 10 + 6; lcd.print("6 received"); break;
    case SEVEN: threshold = threshold * 10 + 7; lcd.print("7 received"); break;
    case EIGHT: threshold = threshold * 10 + 8; lcd.print("8 received"); break;
    case NINE: threshold = threshold * 10 + 9; lcd.print("9 received"); break;
  }
  return;
}
/* this function takes the angle to write it to servo
   and computes the distance of ultrasonic sensor
   then writes both angel and distance in the port of the serial.
*/
void radar_controller(int angle) {

  radarServo.write(angle);
  delay(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distinCM = duration * 0.034 / 2;

  Serial.print(angle);
  Serial.print("*");
  Serial.print(distinCM);
  Serial.print("#");
}

void setup()
{
  Serial.begin(9600);

  /* LCD */
  //analogWrite(6, Contrast);
  lcd.begin(16, 2);
  lcd.clear();

  /* ULTRASONIC */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /* Flame */
  pinMode (flame_sensor_pin , INPUT); // declaring sensor pin as input pin for Arduino
  pinMode(flameoutput, OUTPUT);     // Define pins led
  digitalWrite(flameoutput, LOW);

  /* SERVO */
  radarServo.attach(servopin);

  /* LM35 & IR */
  pinMode(LM_pin, INPUT);   // LM_pin is the input temperature
  pinMode(LMOUTPUT, OUTPUT);     // Define pins led
  digitalWrite(LMOUTPUT, LOW);
  IR_recv.enableIRIn();     //start the receiver
  IR_recv.blink13(true);
  threshold = 0.0;                  //initial the string by null
  currentThreshold = 30.0;
}

void loop()
{
  ///////////// START OF LM35  & LCD /////////////////
  lcd.clear();
  sensorValue = analogRead(LM_pin);       // read the input temprature in millivolt
  Celsius = (sensorValue * 500 / 1024);  // convert from millivolt to celsius
  lcd.setCursor(1, 1);
  lcd.print("Celsius: ");
  lcd.setCursor(9, 1);
  lcd.print(Celsius);

  if (IR_recv.decode(&results)) {
    switch (results.value) {
      case OK: {
          currentThreshold = threshold;
          lcd.setCursor(1, 0);
          lcd.print("Threshold: ");
          lcd.setCursor(11, 0);
          lcd.print(currentThreshold);
          threshold = 0;
        } break;
      default: append();
    }
    //delay(50);                    // Add delay to prevent false readings
    IR_recv.resume();             // receive the next value
  }
  if (Celsius > currentThreshold) {
    digitalWrite(LMOUTPUT, HIGH);
  } else {
    digitalWrite(LMOUTPUT, LOW);
  }
  delay(500);

  ///////////// FLAME SENSOR & ULTRASONIC & SERVO MOTOR //////////////////////////
  /* flame */
  //////////////////// START OF FLAME ///////////////////////
  flame_pin = digitalRead ( flame_sensor_pin ) ; // reading from the sensor
  if (flame_pin == LOW ) // applying condition
  {
    digitalWrite(flameoutput, HIGH);
    ///////////////////// START OF SERVO & ULTRA SONIC ////////////////////
    for (int angle = 0; angle < 180; angle++)
    {
      radar_controller(angle);
    }

    for (int angle = 179; angle >= 0; angle--)
    {
      radar_controller(angle);
    }
  }else{
    digitalWrite(flameoutput, LOW);
  }
}
