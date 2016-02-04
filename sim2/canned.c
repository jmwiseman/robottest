#include"tank.h"
#include"robot.h"
#include"stdio.h"
#include<math.h>
#define SPEED 64
#define WIDTH 6.25
#define W WIDTH
#define FR *100.0
#define RF /100.0
extern int dstat;
int side=-1;
int speed=SPEED;
tank ctank;

#define WEEL_SIZE (2+(1/16))
void c_status(char *message, int n) {
	static int callcount=0;
	if(callcount >10) {
		printf("STATUS: DIST:%d\t%d\t%s %d\n\r",encoderGet(l_encoder),encoderGet(r_encoder),message,n);
		callcount=0;
	}
	callcount=callcount+1;
}
int degrees(int d) {
	return (d*(PI)/180);
}
int radians(int a) {
	return (a*180)/PI;
}
int inches(int l) {
	return radians(l)*WEEL_SIZE;
}

int gofor(int llen, int rlen, int turn, int forward) {
	encoderReset(r_encoder);
	encoderReset(l_encoder);
	int ol=0;
	int or=0;
	dstat=0;
	printf("going for %d\t%d degrees with dir %d\t%d\n\r",llen,rlen,turn,forward);
#ifndef SIM
	while((abs(encoderGet(l_encoder))<llen &&abs(encoderGet(r_encoder))<rlen)){
		c_status("gofor",llen);
		controldrive(turn,forward);
		simtank(&ltank,encoderGet(l_encoder-ol)-ol,encoderGet(r_encoder)-or);
		ol=encoderGet(l_encoder);
		or=encoderGet(r_encoder);
		delay(20);
	}
#endif
	dstat=1;
	controldrive(0,0);
	printf("Motion complete, expected:");
	printpos(&ctank);
	printf("\tintegrated: ");
	printpos(&ltank);
	printf("\n\r");
	return encoderGet(l_encoder)>encoderGet(l_encoder) ? encoderGet(l_encoder) : encoderGet(r_encoder);
}
int s(int l) {
	simtank(&ctank,l,l);
	return gofor(inches(l)/2,inches(l)/2,0,speed);	

}
int r(int a){
	rotate(&ctank,(side*a) RF);
	return gofor(((radians((a)*WIDTH)/2)RF),((radians((a)*WIDTH)/2)RF),speed*side,0);
}
int l(int a){
	rotate(&ctank,(-side*a) RF);
	return gofor(((radians((a)*WIDTH)/2)RF),((radians((a)*WIDTH)/2)RF),-speed*side,0);
}
void fire(int n) {
	printf("fire\n\r\n\r");
	shoot(MAX_SPEED);
	delay(2000);
	load(CONVEYER_SPEED);
	delay(2000*n);
	load(0);
	shoot(0);
}
 
void canned() {
	printf("autonav\n\r");
	//s(12);	
	//l(PI FR);
	speed=SPEED;
	s(5);
	printf("point to first balls\n\r");
	l(
		atan((W/2)/(2+(W/2)))
	FR);
	suck(MAX_SPEED);
	s(sqrt(pow(W/2,2)+pow(2+(W/2),2)));//go to bals
	loadall(CONVEYER_SPEED);
	s(7);//suck up balls
	s(8);//continue
	delay(50);
	r((
		(PI/2)
		//-(PI/16)
	//	- atan((W/2)/(2+(W/2)))

	)FR);
	s(9);
	suck(0);
	fire(4);
	load(0);
	printf("done autonav\n\r");
}
