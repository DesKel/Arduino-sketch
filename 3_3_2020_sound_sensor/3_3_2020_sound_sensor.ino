#define soundPin A0

void setup() {
  Serial.begin(115200);
  pinMode(soundPin,INPUT);
}

void loop() {
  int val = analogRead(soundPin);
  Serial.println(val);
  delay(1);
}
