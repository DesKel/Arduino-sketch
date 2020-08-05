#include <Servo.h>

#define SERVO_PIN  9

Servo servo;

void setup()
{
    servo.attach(SERVO_PIN);
}

void loop()
{
   /* Servo stopped */
  servo.writeMicroseconds(1500);          
  delay(1000);
  /* Servo forward half speed */
  servo.writeMicroseconds(1750);            
  delay(1000);
  /* Servo forward full speed */
  servo.writeMicroseconds(2000);             
  delay(1000);
  /* Servo forward half speed */
  servo.writeMicroseconds(1750);           
  delay(1000);
  /* Servo stopped */
  servo.writeMicroseconds(1500);            
  delay(1000);
  /* Servo backwards half speed */
  servo.writeMicroseconds(1250);            
  delay(1000);
  /* Servo backwards full speed */
  servo.writeMicroseconds(1000);            
  delay(1000);
  /* Servo backwards half speed */
  servo.writeMicroseconds(1250);            
  delay(1000);  
}
