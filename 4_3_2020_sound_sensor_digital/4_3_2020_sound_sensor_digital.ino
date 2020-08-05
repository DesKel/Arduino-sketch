//Signal pin on pin 2
#define soundPin 2

void setup() {
//Begin the serial on 115200 baud rate
  Serial.begin(115200);
  pinMode(soundPin,INPUT);
}

void loop() {
//Read sound sensor module's signal pin. boolean declaration for true (1) and flase (0).
  boolean val = digitalRead(soundPin);

//Print output when the sound signal above the threshold
  if(val == true) Serial.println("Threshold reaches");
  delay(1);
}
