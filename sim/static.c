#include <stdio.h>
#include <stdlib.h>
#include <sim.h>
#include <math.h>
#define SIMTIME 1000
int axis;
int value;
int bad=0;
int good=0;
int iterations;
//static tests
int sign (int a) {
	if(a==0)
		return 0; //+1!=0!=-1
	return abs(a)/a;
}
void die(char *a) {
	printf("\n %s\nbad:%d\ngood:%d / %d\n",a,bad,good,iterations);
	if(bad==0 && good==iterations)
		printf("All PASSED!\n");
	else
		printf("some failures\n");
	exit(0);
}
void sim_nextjoy() {
	axis=(sim_clock/20)%5;
	value=(((sim_clock/40)%3)*200)-200;
	int i=0;
	for(i=0;i<11;i++)
		joy[i][AXIS]=0;
	joy[axis][AXIS]=value;
	printf("time: %ld axis:%d value:%d\n",sim_clock,axis,value);
}
void status() {
	int pass=0;
	if(
	(sim_motors[1] != sim_motors[2])||
	(sim_motors[3] != sim_motors[4])) {
		printf("Mortors are fighting against eachother!!");
		bad=bad+1;
		pass=-1;
	}else {
		if(axis==1) { //forward backward
			if(
			sign(sim_motors[1])==sign(sim_motors[3]) && 
			sign(sim_motors[1])==sign(value)) {
				pass=1;
				good=good+1;
			}else 
				pass=-1;

		}
	
		if(axis==3) { //left right
			if(
			sign(sim_motors[1])!=sign(sim_motors[3]) && 
			sign(sim_motors[1])==sign(value)) {
				pass=1;
				good=good+1;
			}else 
				pass=-1;
			
		}
	}//motor fight else
	printf("Good: %d Bad: %d Drive Motors: %d %d %d %d \n ",good,bad,
	sim_motors[1],
	sim_motors[2],
	sim_motors[3],
	sim_motors[4]);
	if(pass>=0)
		printf("\tPass\n");
	else
		printf("\tFail\n");
}
void sim_housekeeping() {
	iterations+=1;
	status();
	sim_nextjoy();
	if(sim_clock>SIMTIME){
		die("done");
	}
}
int main() {
	printf("testing...\n");
	operatorControl();
	return 0;
}
