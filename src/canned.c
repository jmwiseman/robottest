#include<auto.h>
#include<API.h>
#include<tank.h>
#include<robot.h>
#include<main.h>
#include<math.h>
#define SPEED 64
#define WIDTH 6.25
#define W WIDTH
#define FR *10
extern int dstat;

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
	dstat=0;
	printf("going for %d\t%d degrees\n\r",llen,rlen);
	while((abs(encoderGet(l_encoder))<llen &&abs(encoderGet(r_encoder))<rlen)){
		c_status("gofor",llen);
		controldrive(turn,forward);
		delay(20);
	}
	dstat=1;
	return encoderGet(l_encoder)>encoderGet(l_encoder) ? encoderGet(l_encoder) : encoderGet(r_encoder);
}
int s(int l) {
	return gofor(inches(l)/2,inches(l)/2,0,SPEED);	
}
int l(int a){
	return gofor(radians(10*a/WIDTH)/2,radians(10*a/WIDTH)/2,SPEED,0);
}
 
void canned() {
	printf("autonav\n\r");
	//s(12);	
	//l(PI FR);
	l(atan((W/2)/(2+(W/2)))*10);
	suck(MAX_SPEED);
	s(sqrt(pow(W/2,2)+pow(2+(W/2),2)));
	s(12);
	suck(0);
	printf("done autonav\n\r");
}
