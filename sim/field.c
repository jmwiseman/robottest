#include <sim.h>
#include <tank.h>
#include <math.h>
typedef struct tapeline {
	double a;
	double b;
	double c;
	double start;
	double stop;
} tapline;
tapline field[8];
double ldist(double x,double y,tapline tl){
	return fabs((tl.a*x)+(tl.b*y)+tl.c)/sqrt(pow(tl.a,2)+pow(tl.b,2));
}

void sim_setsensors(tank *v) {
	v->battery=v->battery-0.0001;
}
