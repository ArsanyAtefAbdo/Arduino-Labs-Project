#include <LiquidCrystal.h> 
int Contrast=75;
 LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  
 void setup()
 {
   // analogWrite(6,Contrast);
     lcd.begin(16, 2);
     lcd.print("HELLO, WORLD!");
  } 
     void loop()
 { 
     lcd.setCursor(0, 1);
     //lcd.print("Only Innovative");
   
    //lcd.setCursor(0, 1);
     lcd.print(millis() / 1000);
 }
