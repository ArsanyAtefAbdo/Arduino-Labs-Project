# Arduino-Labs-Project
Arduino Labs and project in Microprocessor class

Lab1 (Remote Control Motor):
----------------------------
Use any Infrared remote control (Receiver or TV remote should work) as a controller for a servo motor by directing the IR beam to the IR receiver (1838).
You are required to make the motor rotate according to the number you send. For example: in order to make the motor rotate at 180 degrees, you send ‘1’ then ‘8’ then ‘0’ then ‘Menu’ or any other function key and the motor should perform the correct rotation. The Volume up and down keys should make the motor angle increase or decrease by 10 degrees. Use an external supply (9V battery) for the motor and attach one of the gears to the motor to show its current position.
NOTE: In order to read the value of each remote control button you have to use an external library:
https://github.com/z3t0/Arduino-IRremote
Please read the library documentation and how to use it since there will be a collision with the RobotIRremote library that comes already with the Arduino software. One approach is to delete the RobotIRremote, the other is to simply rename the downloaded library files and includes to another name.

Lab2 (Temperature warning system):
----------------------------------
- Use the LM35 to measure the current air temperature and print the readings in Centigrade (C) on the serial monitor.
- Use the IR receiver (IR1383) to set a temperature threshold using your remote control. You should assume that the user will enter any number of digits and then click “OK button” to set the threshold.
- If the temperature exceeds this threshold) , a buzzer and an LED must turn ON. If it drops below (threshold -1) then the LED and buzzer should stop.
- In order to read the value of each remote control button you have to use an external library:https://github.com/z3t0/Arduino-IRremote
Please read the library documentation and how to use it since there will be a collision with the RobotIRremote library that comes already with the arduino software. One approach is to delete the RobotIRremote , the other is to simply rename the dowloaded library files and includes to another name.

Lab3 (Morse Code):
------------------
International Morse code is composed of five elements:
• short mark, dot or "dit" (·) : "dot duration" is one time unit long
• longer mark, dash or "dah" (–) : three time units long
• inter-element gap between the dots and dashes within a character : one dot duration or one unit long
• short gap (between letters) : three time units long
• medium gap (between words) : seven time units long
SOS --> … — — — …

Lab4 (Morse Code):
------------------
What is new in this lab ?
• Here each two groups will work together in order to implement SOS signal by using NRF24l01 which will work as sender of the word on one arduino and work as a reciever on the other arduino which will recive the word and encode it as the pervious lab.
Helpful Resources
 https://electropeak.com/learn/wireless-communication-w-arduino-and-nrf24l01/
 https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/

Project (Radar of flame with measuring temperature):
----------------------------------------------------
-Detecting if there is fire (flame) and detect its place using ultrasonic sensor attached on servo on the screen using processing program (i.e. like a radar) in addition to measuring room temperature.
- Enter the threshold that depend on measuring the room temperature using remote control through IR receiver. - If room temperature increases above the threshold, there are buzzer and led will be turned on - If there is a flame, the flame sensor will be turned on, then the servo and ultrasonic sensor will be turned on to detect where is the bodies on screen of “processing” program (i.e. like a radar). - printing on the LCD the room temperature and the threshold.
