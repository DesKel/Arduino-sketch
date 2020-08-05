//define relay pin on pin3
#define relayPin 3

void setup() {
//Begin the serial on 115200 baud rate
  Serial.begin(115200);
  pinMode(relayPin,OUTPUT);
}

void loop() {
//Turn on the LED
  Serial.println("Status: LED on");
  digitalWrite(relayPin,HIGH);
  delay(5000);

//Turn off the LED
  Serial.println("Status: LED off");
  digitalWrite(relayPin,LOW);
  delay(2000);
}
