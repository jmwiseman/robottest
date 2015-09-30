#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <fcntl.h>
int sim_joyfd;
int joy[11][2]; //larger then it neeeds to be
long sim_clock=0;
void sim_delay(int ms) {
	usleep(ms*100);
}
void sim_joyinit() {
	sim_joyfd=open("/dev/input/js1",O_RDONLY|O_NONBLOCK);
	if(sim_joyfd)
		printf("joystick open\n");
}
void sim_setmotor(int channel, int speed) {
	printf("M\t%ld\t%d\t%d\n",sim_clock,channel,speed);
}
void sim_getjoyevents() {
	struct js_event e;
	while(read (sim_joyfd, &e, sizeof(e))>0) {
		if(e.type <3){
			joy[e.number][e.type]=e.value;//evil joysticks can break this
		}
	}
}
int main () {
	printf("Hello world\n");
	sim_joyinit();
	while(1) {
		sim_getjoyevents();
		sim_delay(20);
		sim_clock=sim_clock+20;
	}
	return 0;
}
