#include <unistd.h>
#include "../include/robot.h"
#include <tank.h>
#include <sim.h>
double scale=0.01;
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
void plottank(tank *v) {
	fprintf(fp,"%f %f\n",(v->x)*scale,(v->y)*scale);
}
void controltank(tank *v) {
	v->battery=v->battery-0.001;
	v->lspeed=sim_motors[MO_LEFT1]/10; //TODO: this needs pi somewhere
	v->rspeed=sim_motors[MO_RIGHT1]/10;
}

void simloop(tank *v){
	controltank(v);
	simtank(v);
	plottank(v);

}
void initplot(){
	fp= fopen("path.dat","w");
	if(!fp) 
		sim_die("file open error\n");
	fprintf(fp,"# X Y\n");
}
void finishplot() {
	fclose(fp);	
	system("gnuplot -e \"set term dumb ;plot 'path.dat'\"");
}
void simend() {
	finishplot();
	exit(0);
}

void sim_housekeeping() {
	//printf(".");
	sim_setsensors(&timothy);
	simloop(&timothy);
	if(timothy.battery<=0)
		simend();

}
void siminit() {
	timothy.battery=100;
	initplot();
}
int main() {
	siminit();
	printf("simulating... \n");
	autonomous();
	simend();
	return 0;
}

