#include <stdio.h>
#include <stdlib.h>
#include <sim.h>
#define SIMTIME 1000
//static tests
int axis,value=0;
void sim_nextjoy() {
	axis=(sim_clock/20)%5;
	value=(((sim_clock/40)%3)*200)-200;
	int i=0;
	for(i=0;i<11;i++)
		joy[i][AXIS]=0;
	joy[axis][AXIS]=value;
	printf("time: %ld axis:%d value:%d\n",sim_clock,axis,value);
	
}
void checkmotors(){
	/*1+ forward
	 *  20 1- backward
	 *   21 3+ all motors +
	 *    22 3- all motors - */
}
void sim_housekeeping() {
	checkmotors();
	sim_nextjoy();
	if(sim_clock>SIMTIME){
		printf("done\n");
		exit(0);
	}
}
int main() {
	printf("testing...\n");
	operatorControl();
	return 0;
}
