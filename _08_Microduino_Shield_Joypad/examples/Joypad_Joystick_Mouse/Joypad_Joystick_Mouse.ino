/*
 Joypad Joystick Mouse 
 Thanks:Tom Igoe
 */

#define JOYSTICK_DEAD_ZONE 50

#include <Joypad.h>

void setup()
{
  Serial.begin(115200);       // initialize serial communication with your computer
  Mouse.begin();            // take control of the mouse
  delay(1000);
} 

void loop()
{
  int xValue,yValue,xC,yC;

  xC=Joypad.readJoystickX();
  if(abs(xC)>JOYSTICK_DEAD_ZONE)
  {
    if (xC>0)
      xValue = xC-JOYSTICK_DEAD_ZONE;
    else
      xValue = xC+JOYSTICK_DEAD_ZONE;
  }
  else
    xValue=0;

  yC=Joypad.readJoystickY();
  if(abs(yC)>JOYSTICK_DEAD_ZONE)
  {
    if (yC>0)
      yValue = yC-JOYSTICK_DEAD_ZONE;
    else
      yValue = yC+JOYSTICK_DEAD_ZONE;
  }
  else
    yValue=0;

  boolean button=Joypad.readButton(CH_JOYSTICK_SW);

  Serial.print("Joystick X: ");                // print a label for the X value
  Serial.print(xValue);                        // print the X value
  Serial.print("\tY: ");                       // print a tab character and a label for the Y value
  Serial.print(yValue);                        // print the Y value
  Serial.print("\tButton: ");                       // print a tab character and a label for the Y value
  Serial.println(button);

  int mouseX = map( xValue,-512, 512, -10, 10);  // map the X value to a range of movement for the mouse X
  int mouseY = map( yValue,-512, 512, -10, 10);  // map the Y value to a range of movement for the mouse Y

  Mouse.move(mouseX, mouseY, 0);                 // move the mouse

  if (!button) 
  {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) 
      Mouse.press(MOUSE_LEFT); 
  } 
  // else the mouse button is not pressed:
  else 
  {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) 
      Mouse.release(MOUSE_LEFT); 
  }

  delay(10);                                  // a short delay before moving again
}
