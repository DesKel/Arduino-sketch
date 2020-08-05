#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Pin define
int sensePin = A0;
int ledPin = 14; //D4, GPIO2

//Fixed parameter
int Tsampling = 280;
int Tdelta = 40;
int Tsleep = 9680;

//Variable parameter
int ave_sample = 150;
float offset = 0.64;
String level = "";

//Output define
float outVo = 0;
float sigVolt = 0;
float dustLevel = 0;

//Serial debug, 0- disable, 1 - enable
boolean debug = 0;

//LCD IIC parameter
LiquidCrystal_I2C lcd(0x3F,16,2); 

//WiFi setup
#include <ESP8266WiFi.h>
String SSID = "The_Patriot";
String password = "DestructiveKelvin1992";
WiFiClient client;

//Thingspeak setup
String host = "api.thingspeak.com";
int port = 80;
String API = "NRIFQ4GZY5CF7UDF";
 
void setup(){
  if(debug == 1) Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  lcd.init(); 
  lcd.backlight();
  WiFi.begin(SSID, password);

  if (debug == 1) Serial.println("Wait for WiFi... ");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting ");
  lcd.setCursor(0,1);
  while (WiFi.status() != WL_CONNECTED) 
  {
    lcd.print(".");
    if (debug == 1) 
    {
       Serial.print(".");
    }
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connected ");
  lcd.setCursor(0,1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());

  if (debug == 1)
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  delay(1000);
}
 
void loop(){
  
  //Reset cumulative
  float cumu_dustLevel = 0;
  
  for(int i=0; i<ave_sample; i++)
  {
    digitalWrite(ledPin,LOW); 
    delayMicroseconds(Tsampling);
   
    outVo = analogRead(sensePin); 
   
    delayMicroseconds(Tdelta);
    digitalWrite(ledPin,HIGH); 
    delayMicroseconds(Tsleep);
   
    sigVolt = outVo * (3.3 / 1024) +offset;
    dustLevel = (0.17 * sigVolt - 0.1)*1000;
    cumu_dustLevel += dustLevel;
    delay(100);
  }

  //Averaage dust level
  dustLevel = cumu_dustLevel/ave_sample;

  //Health level
  if (dustLevel<=35) level="Excellent";
  else if (dustLevel>35 && dustLevel <=75) level="Average";
  else if (dustLevel>75 && dustLevel <=115) level="Light Po";
  else if (dustLevel>115 && dustLevel <=150) level="Moder. Po";
  else if (dustLevel>150 && dustLevel <=250) level="Heavy Po";
  else if (dustLevel>250 && dustLevel <=500) level="Serious Po";

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dust: ");
  lcd.print(dustLevel);
  lcd.setCursor(0,1);
  lcd.print("Lvl: ");
  lcd.print(level);

  //Upload data
  if (client.connect (host,port))
  {
    String data = API;
    data += "&field1=";
    data += String(dustLevel);
    data += "\r\n\r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+API+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);
  }

  if (debug == 1)
  {
    Serial.print("Measured Signal Value (0-1023): ");
    Serial.print(outVo);
    Serial.print("   Voltage: ");
    Serial.print(sigVolt);
    Serial.print("   Dust Density Level: ");
    Serial.println(dustLevel);
  }
}
