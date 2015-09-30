#include <stdbool.h>
void motorSet(int channel, int speed); 
int joystickGetAnalog (unsigned char joystick, unsigned char axis);
bool joystickGetDigital (unsigned char joystick, unsigned char axis); 
void delay(int t); 
