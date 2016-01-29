#include<auto.h>
#include<API.h>
#include<tank.h>
#define WEEL_WIDTH 4
#define ROBOT_WIDTH 7.45
#define PI 3.141592654
double f_tile_len=20;
#define f_center_x f_tile_len
#define f_center_y 2*f_tile_len
#define f_shot_x f_tile_len*2
#define f_shot_y f_tile_len*3

extern void controldrive(int turn,int forward);
void simtank(tank *v,int dl, int dr) {
	//the change in heading is the difference of the speeds
	//the change in location is the sum of the two as the hypotonuse of the triangle where heading is the angle
	//except that the motors are flipped in polarity so invert all that
	//except we now the encoders are flipped so we don't
	double lspeed=dl*0.1;
	double rspeed=dr*0.1;
	double r=(lspeed+rspeed)/2;
	double dh;
	//if(fabs(lspeed-rspeed)>100)
//		v->h=v->h+((lspeed-rspeed))/33.0;//TODO: use math
	if(lspeed>rspeed)
		dh=((lspeed-rspeed)/10)*((lspeed*WEEL_WIDTH)/ROBOT_WIDTH);
	else
		dh=((lspeed-rspeed)/10)*((rspeed*WEEL_WIDTH)/ROBOT_WIDTH);
	v->h=v->h+dh;
	if(v->h>2*PI)
		v->h=v->h-2*PI;
	if(v->h<0)
		v->h=v->h+2*PI;

	v->x=v->x+(r*cos(v->h));
	v->y=v->y+(r*sin(v->h));
}
void printpos(tank *v) {
	printf("POSITION: x:%f\t y:%f\t HEAD: %f",v->x,v->y,v->h);
}
double headingto(tank v, double x, double y) {//return heading to target from current position
	//     robotpositionvector + newoffsetvector = targetpositionvector
	//=>   robotpositionvector - targetpositionvector = -newoffsetvector
	//=> -(robotpositionvector - targetpositionvector) = newoffsetvector
	//=>  -robotpositionvector + targetpositionvector = newoffsetvector
	double nx,ny;
	nx=-v.x+x;
	ny=-v.y+y;
	return 	atan2(nx,ny);
}
double distanceto(tank v, double x, double y) {
	return sqrt(pow((v.x-x),2)+pow((v.y-y),2));
}
void driveto(tank v, double x, double y) {
	int turn =ceil((headingto(v,x,y)-v.h)*50);
	int forward=ceil((distanceto(v,x,y)));
	forward=0;
	controldrive(turn,forward);
	
}
void b_driveto(tank v,double x, double y, double r) {
	if(r==0)
		r=5;
	while(distanceto(v,x,y)>r) {
		printf("DISTANCE: %f\n\r",distanceto(v,x,y));
		driveto(v,x,y);
		delay(20);
	}
}
void drivetogoal(tank v) {
	//drive near center of map then use elijah line follow code + range sensor
	//reset position to in front of goal
	b_driveto(v,f_center_x,f_center_y,20);
	elf();
}

