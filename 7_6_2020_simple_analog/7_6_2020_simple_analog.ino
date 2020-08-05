//simple analog read

void setup() 
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() 
{
  int val = analogRead(A0);
  Serial.println(val);
  delay(1000);
}
