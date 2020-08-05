//Signal pin on A0 (analog)
//Power pin on 3 (digital)
#define waterPin A0
#define powerPin 3

void setup() {
  //Initialize serial baud rate
  Serial.begin(115200);

  //set pin mode
  pinMode(waterPin,INPUT);
  pinMode(powerPin,OUTPUT);
}

void loop() {
  //turn on power pin and take reading
  digitalWrite(powerPin,HIGH);
  int val = analogRead(waterPin);
  Serial.print("Analog raw value: ");
  Serial.println(val);

  //Turn off power pin and get idle for 1s
  digitalWrite(powerPin,LOW);
  delay(1000);
}
