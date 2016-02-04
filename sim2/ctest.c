#include "tank.h"
#include <stdio.h>
#include "robot.h"
//cc canned.c tank.c ctest.c -lm -o sim && ./sim
//needs tank.h (auto.h?)

//comment out the encoders and stuff
//
extern void canned();
void load(int a) {
	printf("load\n");
}
void loadall(int a) {
	printf("loadall\n");
}
void shoot(int a){
	printf("shoot\n");
}
int encoderGet(void *a){
	return 0;
}
void encoderReset(void *a){
}
void delay(int a){
}
void controldrive(int turn, int forward){
}
void suck(int a){
	printf("suck\n");
}
void finish() {
	printf("\n\nDone\n");
}

int main() {
	canned();
	finish();
	return 0;
}

