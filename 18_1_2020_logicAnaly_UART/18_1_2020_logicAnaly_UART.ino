#include <SoftwareSerial.h>

SoftwareSerial serial(8,7);

void setup() {
  serial.begin(9600);
}

void loop() {
  serial.println("hello world");
  delay(3000);
}
