#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#define PI 3.14159
double scale=0.1;
typedef struct tank {
	double x,y,h;
	double lspeed,rspeed;
	double width;//not necesary?
	double battery;
} tank;
int simtank(tank *v) {
	//the change in heading is the difference of the speeds
	//the change in location is the sum of the two as the hypotonuse of the triangle where heading is the angle
	//except that the motors are flipped in polarity so invert all that
	double r=v->lspeed-v->rspeed;
	v->h=v->h+v->lspeed+v->rspeed;
	v->x=v->x+(r*cos(v->h));
	v->y=v->y+(r*sin(v->h));
	v->battery=v->battery-(v->lspeed-v->rspeed);//TODO:speed should change based on battery
}
void plottank(tank *v, FILE *fp) {
		fprintf(fp,"%f %f\n",v->x*scale,v->y*scale);
}
void controltank(tank *v) {
	v->battery=v->battery-0.001;
	v->lspeed=1;
	v->rspeed=0;
}

void simloop(tank *v,FILE *fp){
	v->battery=1000;
	while(v->battery>0){
		controltank(v);
		simtank(v);
		plottank(v,fp);
	}

}

int main() {
	tank v;
	FILE *fp= fopen("path.dat","w");
	fprintf(fp,"# X Y\n");
	simloop(&v,fp);
	fclose(fp);	
	system("gnuplot -e \"set term dumb ;plot 'path.dat'\"");
	return 0;
}
