#include<auto.h>
#include<API.h>
#include<tank.h>
extern void controldrive(int turn,int forward);
void simtank(tank *v,int dl, int dr) {
	//the change in heading is the difference of the speeds
	//the change in location is the sum of the two as the hypotonuse of the triangle where heading is the angle
	//except that the motors are flipped in polarity so invert all that
	//except we now the encoders are flipped so we don't
	double lspeed=dl*0.1;
	double rspeed=dr*0.1;
	double r=(lspeed+rspeed)/2;
	//if(fabs(lspeed-rspeed)>100)
		v->h=v->h+((lspeed-rspeed))/33.0;//TODO: use math

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
	controldrive(turn,forward);
	
}
void b_driveto(tank v,double x, double y, double r) {
	if(r==0)
		r=1;
	while(distanceto(v,x,y)<r) 
		driveto(v,x,y);
}
