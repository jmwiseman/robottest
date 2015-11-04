#include <sim.h>
#include <tank.h>
#include <math.h>
typedef struct tapeline {
	double x1;
	double x2;
	double y1;
	double y2;
}tapeline;
tapeline field[8];
double ldist(double x,double y,tapeline l){
	double m=(l.y2-l.y1)/(l.x2-l.x1);
	double b= l.y1/(m*l.x1); //y=mx+b => y/mx=b
	//
	//distance function: d^2=(x2-x1)^2 + (y2-y1)^2
	//the distance between a  functin and a point will be the min [ distance(pt,f(x))] 
	//√(p-f(x))^ 2
	//0 = x^2 +mx +2mp.y -b+2p.x +1
	//
	double r= (x - m*b +m*y)/(m*m+1);
	printf("distance: %f\n\n",r);
	
	return r;
}

void sim_setsensors(tank *v) {
	v->battery=v->battery-0.0001;
	tapeline t;
	t.x1=0;
	t.x2=1;
	t.y1=0;
	t.y2=1;
	analogs[1]=ldist(v->x,v->y,t);
}
