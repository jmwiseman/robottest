#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#define AXIS 2
#define BUTTON 1
extern void operatorControl(void);
int sim_joyfd;
int joy[11][2]; //larger then it neeeds to be
int sim_motors[11];
long sim_clock=0;
void sim_delay(int ms) {
	usleep(ms*10000);
	sim_clock=sim_clock+ms;
}
void sim_joyinit() {
	sim_joyfd=open("/dev/input/js1",O_RDONLY|O_NONBLOCK);
	if(sim_joyfd)
		printf("joystick open\n");
}
void motorSet(int channel, int speed) {
	if(channel<11)
		sim_motors[channel]=speed;
}
void sim_getjoyevents() {
	struct js_event e;
	while(read (sim_joyfd, &e, sizeof(e))>0) {
		if(e.type <3){
			joy[e.number][e.type]=e.value;//evil joysticks can break this
		}
	}
}
int joystickGetAnalog (unsigned char joystick, unsigned char axis) {
	return joy[axis][AXIS]/100;
}
bool joystickGetDigital (unsigned char joystick, unsigned char axis) {
	return joy[axis][BUTTON]==0; 
}
void sim_ui()
{
	int i;
	//printf("\033[;f");//home cursor
	printf("\033[2J\n");
	puts("\nMotors:");
	for(i=0;i<11;i++) {
		printf("%d\t",sim_motors[i]);
	}
	puts("\nJoystick");
	for(i=0;i<5;i++){
		printf("%d\t",joy[i][AXIS]);
	}
	puts("\nButtons");
	for(i=0;i<11;i++){
		printf("%d\t",joy[i][BUTTON]);
	}
}
void sim_housekeeping()
{
	sim_ui();
	sim_getjoyevents(); 
}
void delay(int t) {
	sim_delay(t);
	sim_housekeeping();
}
int main () {
	printf("\033[2J\n");
	sim_joyinit();
	operatorControl();
	return 0;
}
