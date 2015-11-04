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
	//distance function: roo((x2-x1)^2 - (y2-y1)^2)
	//the distance between a  functin and a point will be the min [ distance(pt,f(x))] 
	//so d/dx[sqrt(x2-((y-b)/m)-(y2-(mx+b)))]=0
	double r=0;
	return r;
}

void sim_setsensors(tank *v) {
	v->battery=v->battery-0.0001;
}
