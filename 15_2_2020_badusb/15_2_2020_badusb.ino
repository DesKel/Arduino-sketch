#include <Keyboard.h>

void press_enter()
{
  Keyboard.press(KEY_RETURN); //Press enter key
  Keyboard.release(KEY_RETURN); //Release enter key
  delay(500);
}

void setup()
{
Keyboard.press(KEY_LEFT_GUI); //Press windows key
delay(500);
Keyboard.press('r'); //Press 'r' key
Keyboard.releaseAll(); // Release to execute "wins + r", which is run.
delay(500);
Keyboard.print("cmd"); //Type 'cmd'
press_enter();
Keyboard.print("ipconfig"); // Payload
press_enter();
while(1); // Important! It stops loop execution.
}

void loop()
{
  //Nothing
}
