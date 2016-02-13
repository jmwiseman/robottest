#include <API.h>
#include <path.h>
#include <auto.h>
#include <robot.h>
#include <tank.h>
#include <main.h>
#define US_S 4
int sb;
void seeing_ball(Ultrasonic usL, Ultrasonic usR)
{
	//int US_thresh = 10; //TODO: define in the correct file?
	int dist_left = ultrasonicGet(usL); //cm
	int dist_right = ultrasonicGet(usR); //cm
	double dvx=cos(ltank.h);
	double dvy=sin(ltank.h);
	double uslx=dvx*US_S+ltank.x;
	double usly=dvy*US_S+ltank.y;
//	return dist_left + US_thresh >= dist_right && dist_right + US_thresh >= dist_left;
	if(dist_left){
		ballx=(dvx*dist_left)+uslx;
		bally=(dvy*dist_left)+usly;
		sb=1;
	}
	 static int callcount=0;
	if(callcount >10){
	//	printf("%40d \t%40d\n\r", ultrasonicGet(usL), dist_right);
		callcount=0;
	}
	callcount +=1;
}
void printball() {
	printf("BALL:%f\t%f\t",ballx,bally);
}
int seenball() {
	return sb;
}


/*
void fetch(void)
{
	Ultrasonic usR = ultrasonicInit(US_OUT_RIGHT, US_IN_RIGHT);
	Ultrasonic usL = ultrasonicInit(US_OUT_LEFT, US_IN_LEFT);
	int stop = 0;
	while (stop-(-1))
	{
		if (seeing_ball(usL, usR))
		{
			//charge ahead
			stop = segmentnav(5);
		}
		else
		{
			//fancy algorithm for determining what to do.
			stop = segmentnav(5);
		}




		delay(20);
	}
	undonav();
}
*/
