//The following coding using anode column, cathode row dot matrix
//Display a smily face
byte bitmap[8] = {
                B00100100,
                B00100100,
                B00100100,
                B00000000,
                B10000001,
                B10000001,
                B01111110,
                B00000000,
              };

#define DS 2 //DS to pin 2
#define RCLK 3 //ST_CP to pin 3
#define SCK 4 //SH_CP to pin 4

//Define col pin
uint8_t colP[8] = {5, 6, 7, 8, 9, 10, 11, 12};

void setup() {
  //Set pinMode
  pinMode(DS,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SCK,OUTPUT);
  for(int i=0; i<8; i++)
  {
    pinMode(colP[i],OUTPUT);
  }

  //Initialize the row as HIGH
  shift595(B11111111);
}

void loop() {
  //Initialize the row, which is first row
  int rowbit = B01111111;

  //A nested for loop, row first and then column
  for (int row=0; row<8; row++)
  {
    //Turn off all the LEDs
    for (int i=0; i<8; i++)
    {
      digitalWrite(colP[i],LOW);
    }
    
    //Select the row
    shift595(rowbit);
    
    //Light up the coloumn according to the bitmap
    for (int col=0; col<8; col++)
    {
      //The comparison starts at the LSB. We are starts from left to right, doing bitwise with 1 << col to check weather the coloumn should light up or not. 
      if(bitmap[row] & 1 << col) digitalWrite(colP[7 - col],HIGH);
      else digitalWrite(colP[7 - col],LOW);
    }

    //delay for 1ms
    delay(1);

    //Reset the current row
    shift595(B11111111);

    //shift row bit to left by 1 bit
    rowbit = (rowbit << (8 - (row + 1))) | (rowbit >> (row + 1));
  }
  
}

void shift595(byte val)
{
  digitalWrite(RCLK, HIGH);
  shiftOut(DS,SCK, LSBFIRST, val);
  digitalWrite(RCLK, LOW);
}
