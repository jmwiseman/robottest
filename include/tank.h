#include <math.h>
#define PI 3.14159
extern void autonomous(void);
typedef struct tank {
	double x,y,h;
	double width;//not necesary?
} tank;
tank ltank;
void sim_setsensors(tank *v);
void simtank(tank *v,int dl, int dr);
void printpos(tank *v);
double headingto(tank v, double x, double y);
double distanceto(tank v, double x, double y);
void driveto(tank v, double x, double y);
void b_driveto(tank v, double x, double y, double r);
void drivetogoal(tank v);


