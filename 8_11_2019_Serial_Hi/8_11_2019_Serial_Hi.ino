void setup() {
  Serial.begin(9600);
  Serial.println("Say Hi!");
}

void loop() {
  while(Serial.available()>0)
  {
    if(Serial.read() == "Hi")
    {
      Serial.println("Hi, nice to meet you");
    }
    else
    {
      Serial.println("Please say HI!");
      Serial.read();
      delay(100);
    }
  }
}
