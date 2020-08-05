#define ACS712 A0

unsigned int x=0;
float AcsIntValue=0.0,AcsValue=0.0,AvgAcs=0.0,AcsValueF=0.0;
int sample = 500; //Hihger the sample rate, more processing time is needed

/**Sensitivity according to ACS712 spec
 * ACS-05: 0.185
 * ACS-20: 0.100
 * ACS-30: 0.066
 **/
float sensitivity = 0.066; 


void setup() 
{
  Serial.begin(115200); //Start Serial Monitor to display current read value on Serial monitor
  pinMode(ACS712,INPUT);
}

void loop() 
{
  AcsValue = 0.0; //Initialized the cumulative value
  for (int x = 0; x < sample; x++)
  { 
    AcsIntValue = analogRead(ACS712);     
    AcsValue = AcsValue + AcsIntValue;  
    delay (3); // let ADC settle before next sample 3ms
  }
  
AvgAcs=AcsValue/float(sample);//Taking Average of Samples

//((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
//2.5 is offset(I assumed that arduino is working on 5v so the viout at no current comes
//out to be 2.5 which is out offset. If your arduino is working on different voltage than 
//you must change the offset according to the input voltage)
AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) )/sensitivity;

Serial.println(AcsValueF);//Print the read current on Serial monitor
delay(50);
}
