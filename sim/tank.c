#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/robot.h"
#define PI 3.14159
extern void autonomous(void);
double scale=0.1;
FILE *fp;
typedef struct tank {
	double x,y,h;
	double lspeed,rspeed;
	double width;//not necesary?
	double battery;
} tank;
tank timothy;
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
	v->rspeed=-1;
}

void simloop(tank *v,FILE *fp){
	controltank(v);
	simtank(v);
	plottank(v,fp);

}
void initplot(FILE *fp){
	fp= fopen("path.dat","w");
	fprintf(fp,"# X Y\n");
}
void finishplot(FILE *fp) {
	fclose(fp);	
	system("gnuplot -e \"set term dumb ;plot 'path.dat'\"");
}
void simend() {
	finishplot(fp);
	exit(0);
}

void sim_housekeeping() {
	printf(".");
	simloop(&timothy,fp);
	if(timothy.battery<=0)
		simend();

}
void siminit() {
	timothy.battery=100;
	initplot(fp);
}
int main() {
	printf("simulating...\n");
	siminit();
	autonomous();
	simend();
	return 0;
}

