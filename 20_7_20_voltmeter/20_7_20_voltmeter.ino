#define in A0

void setup() {
  pinMode(in, INPUT);
  Serial.begin(115200);
}

void loop() {
 int val = analogRead(in);
 float voltage = float(val)/1024.0 *5.0;
 Serial.print("Raw:  ");
 Serial.print(val);
 Serial.print("\tVoltage:  ");
 Serial.println(voltage);
 delay(500);
}
