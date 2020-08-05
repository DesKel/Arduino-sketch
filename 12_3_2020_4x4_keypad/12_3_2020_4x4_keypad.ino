//initialize debouncing parameter
uint8_t debouceR = 0;
uint8_t debouceC = 0;

//Initialize 4x4 key map
char key[4][4] = {
                  {'1', '2', '3', 'A'},
                  {'4', '5', '6', 'B'},
                  {'7', '8', '9', 'C'},
                  {'*', '0', '#', 'D'}
                 };

void setup() {
  //Serial begin at baud rate 115200
  Serial.begin(115200);
  Serial.println("Keypad prototyping, please press the key");
  
  //set pin 2 to pin 5 (row) as input
  for(int i=2; i<6; i++)
  {
    pinMode(i,INPUT_PULLUP);
  }

  //set pin 6 to pin 9 (Column) as output, set HIGH as default
  for(int i=6; i<10; i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  //Initialize row state and column state to 0
  uint8_t r = 0;
  uint8_t c = 0;

  //Activate and deactivate the column one by one
  for(int i=6; i<10; i++)
  {
    digitalWrite(i, LOW);
    //Scan for row
    for(int j=2; j<6; j++)
    {
      if (digitalRead(j) == 0) 
      {
        //Row offset -1 (AS it starts as pin 2), column offset -5 (As it starts as pin 6)
        r = j-1;
        c = i-5;
      }
    }
    digitalWrite(i, HIGH);
  }

  //To print the pressed number, you have to follow 2 conditions
  //Condition 1: The button must be press (c!=0 and r!=0)
  //Condition 2: To avoid duplicated number print out while pressing the key, 
  //             you need debouncing switch (debouceR!=r and debouceC!=c)
  if((c!=0 && r!=0) && (debouceR!=r && debouceC!=c))
  {
    //Array starts with 0. Since c and r cannot be equal to 0, we shift the array by -1 while printing the output.
    Serial.print("Input: ");
    Serial.println(key[r-1][c-1]);
  }

  //Pass the saved state as holding state
  debouceR = r;
  debouceC = c;

  //Include a small delay
  delay(2);
}
