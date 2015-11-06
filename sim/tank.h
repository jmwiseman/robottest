#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159
extern void autonomous(void);
FILE *fp;
typedef struct tank {
	double x,y,h;
	double lspeed,rspeed;
	double width;//not necesary?
	double battery;
	double lsoffset;
	double lswidth;
} tank;
tank timothy;
void sim_setsensors(tank *v);


