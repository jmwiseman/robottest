#include <API.h>
#define JOY_TURN 1
#define JOY_FORWARD 2
#define JOY_INTAKE 5
#define JOY_AUTOTEST_G 8
#define JOY_AUTOTEST_B JOY_LEFT
#define JOY_TARGET JOY_DOWN
#define JOY_INTAKE_B 7
#define JOY_FLYWHEEL 6
#define JOY_DEAD 20
#define JOY_SCALE 2

//#define MO_CONVEYER1 1
//#define MO_CONVEYER2 10
#define MO_CONVEYER1 7
//#define MO_CONVEYER2 8
#define B_CONVEYER 5
#define CONVEYER_SPEED 150

#define MO_INTAKE 6

#define MO_LEFT1 2
#define MO_LEFT2 4
#define MO_RIGHT1 3
#define MO_RIGHT2 5

#define MO_FLY1 8 //C, D
#define MO_FLY2 9 //A, B
#define FLY_SPEED 255

#define LS_LEFT 6
#define LS_CENTER 7
#define LS_RIGHT 8

#define LS_B_L 0b10000000
#define LS_B_C 0b01000000
#define LS_B_R 0b00100000

#define US_IN_RIGHT  6 
#define US_OUT_RIGHT 5//orange
#define US_IN_LEFT   8
#define US_OUT_LEFT  7//orange

#define AUTOSPEED 84
#define MAX_SPEED 128
#define BANK_VALUE 30

#define S_FOLOW 1
#define S_BLIND 2
#define S_TL	3
#define S_TR	4
#define S_SEKL	5

#define ENC_RIGHT_TOP 1
#define ENC_RIGHT_BOT 2

#define ENC_LEFT_TOP  3
#define ENC_LEFT_BOT 4
#define LCD_PORT uart1

#define CON_SWITCH 11
//global varibles
Ultrasonic usR;
Ultrasonic usL;
void controldrive(int turn, int forward);

#define C_TOL 15
#define C_BUMP 15
#define FLYCONTROLSPEED 3400 //only works on full battery.  Overshoots if not full battery
#define FLYHIGHSPEED 3900
