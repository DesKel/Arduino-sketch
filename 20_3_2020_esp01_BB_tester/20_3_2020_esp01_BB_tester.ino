/*
 * ESP8266-01 breakout board tester
 * Date: 20/3/2020
 * Version: 1
 * Description: A simple ESP8266-01 breakout board tester script
 */

/*
 * Pin defination
 * TXD --> Pin 2
 * CHPD --> Pin 3
 * RST --> Pin 4
 * VCC --> Pin 5
 * GND --> Pin 6
 * GP2 --> Pin 7
 * GP0 --> Pin 8
 * RXD --> Pin 9
 */
uint8_t pinIn [8] = {2, 3, 4, 5, 6, 7, 8, 9};
String pinName [8] = {"TXD", "CHPD", "RST", "VCC", "GND", "GP2", "GP0", "RXD"};

void setup() {
  //Begin serial terminal at 115200 bps
  Serial.begin(115200);

  //Initialize pinMode
  for (int i=0; i<8; i++) pinMode(pinIn[i],INPUT_PULLUP);
}

void loop() {
  //Scanning for digital input == LOW and add a delay.
  delay(5);
  for (int i=0; i<8; i++)
  {
    if (digitalRead(pinIn[i]) == LOW)
      {
        //Print the pin check once a GND is connected
        Serial.print(pinName[i]);
        Serial.println(" Checked");
        delay(5);
        
        //Waiting the pin to release
        while(digitalRead(pinIn[i]) == LOW); 
      }
  }
}
