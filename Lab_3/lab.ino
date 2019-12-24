const int ledpin = 8;
int unitdelay = 500;
String input;
char *morse_letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
                         ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                         "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
char *morse_num[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    input = Serial.readString();
    Serial.println(input);
    /* last element in string is length - 2 */
    int len = input.length();
    // Serial.println(len);
    for (int i = 0; i < len-1; i++){
      /* letter small */
      if (input[i] >= 'a' && input[i] <= 'z'){
        turn_on_off(morse_letters[input[i] - 'a']);
      }/* letter capital */
      else if (input[i] >= 'A' && input[i] <= 'Z'){
        turn_on_off(morse_letters[input[i] - 'A']);
      }/* number */
      else if (input[i] >= '0' && input[i] <= '9'){
        turn_on_off(morse_num[input[i] - '0']);
      }/* space character */
      else if (input[i] == ' '){
        delay(unitdelay * 7);
      }
    }
  }
}

void turn_on_off(char* string){
  int j = 0;
  while (string[j] != NULL){
    digitalWrite(ledpin, HIGH);
    if (string[j] == '.'){
      delay(unitdelay);
    }else if (string[j] == '-'){
      delay(unitdelay * 3);
    }
    digitalWrite(ledpin, LOW);
    delay(unitdelay);
    j++;
  }
  delay(unitdelay * 3);
}
