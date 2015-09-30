#include <stdio.h>
#include <stdlib.h>
#include <sim.h>
#define SIMTIME 1000
//static tests
void sim_nextjoy() {
	int axis=(sim_clock/20)%5;
	int value=(((sim_clock/40)%3)*200)-200;
	int i=0;
	for(i=0;i<11;i++)
		joy[i][AXIS]=0;
	joy[axis][AXIS]=value;
	printf("time: %ld axis:%d value:%d\n",sim_clock,axis,value);
}
void status() {
}
void sim_housekeeping() {
	sim_nextjoy();
	if(sim_clock>SIMTIME){
		printf("done\n");
		exit(0);
	}
	status();
}
int main() {
	printf("testing...\n");
	operatorControl();
	return 0;
}
