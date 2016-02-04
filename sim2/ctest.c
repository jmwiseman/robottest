#include "tank.h"
#include <stdio.h>
#include "robot.h"
//cc canned.c tank.c -lm -o sim && ./sim
//needs tank.h (auto.h?)

//comment out the encoders and stuff
//
extern void canned();
void load(int a) {
}
void loadall(int a) {
}
void shoot(int a){
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
}
void finish() {
	printf("\n\nDone\n");
}

int main() {
	canned();
	finish();
	return 0;
}

