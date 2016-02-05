/** @file auto.c
 *
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include <main.h>
#include <../include/robot.h>
#include <auto.h>
#include <path.h>
#include <tank.h>

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
int lss[3];
int going=1;
#define LSAMPLE_LEN
int lsamples[LSAMPLE_LEN];
int lstav;
#define lthreshold 300


void controldrive(int turn, int forward);
int *asense() {//NOT THREAD SAFE
	int ls[3];
	int i=0;
	ls[0]=analogRead(LS_LEFT);
	ls[1]=analogRead(LS_CENTER);
	ls[2]=analogRead(LS_RIGHT);
	int average=(ls[0]+ls[1]+ls[2])/3;
	for( i=0; i<3;i++){
			lss[i]=ls[i]-average;
	}
	//for(i=0; i<LSAMPLE_LEN)

	return &lss[0];
}

void simple_linefollow() {
	//lss[0] == *ls
	//lss[n] == *(ls+n)
	int *ls=asense();
	printf("\t%d",*(ls+1));
	if(abs(*(ls+1))>lthreshold)
	{
		printf("line");
		going=0;
	}
	else
		going=1;
	if(going==1)
		controldrive(20, 70);
	else
		controldrive(0,0);
}


int AUTO_SPEED = 20;
//elijah_linefollow() driving functions
void drive_straight()
{
	controldrive(0,AUTO_SPEED+10);
}
void drive_backward()
{
	controldrive(0,-AUTO_SPEED-10);
}
//bank functions
void bank_right()
{
	controldrive(AUTO_SPEED,AUTO_SPEED);
}
void bank_left()
{
	controldrive(-AUTO_SPEED,AUTO_SPEED);
}
//sharper bank functions
void turn_right()
{
	controldrive(AUTO_SPEED,0);
}
void turn_left()
{
	controldrive(-AUTO_SPEED,0);
}
void search_for_line()
{
	bank_right();//TODO: change this to what it would actually be
}


int turning_back = 0;

void elijah_linefollow()
{
	int *ls=asense();
	int left = *(ls)<-lthreshold;
	int middle = *(ls+1)<-lthreshold;
	int right = *(ls+2)<-lthreshold;
	printf("%d %d %d\n",left,middle,right);
	/*
	//no sensors
	if (!left && !middle && !right)
	{

	}//*/
	//single sensor
	//int lag = 500;
	/*
	if (left && !middle && !right)
	{
		bank_right();
		//delay(lag);
	}
	else if (middle && !right && !left)
	{
		drive_straight();
	}
	else if (right && !left && !middle)
	{
		bank_left();
		//delay(lag);
	}
	else
	{
		drive_straight();
	}//*/

	/*
	//two sensors
	if (left && middle && !right)
	{
		turn_right();
	}
	if (middle && right && !left)
	{
		turn_left();
	}
	//all three sensors
	if (right && left && middle)
	{
		turn_right();
	}//*/


	if (middle && !right && !left)
	{
		bank_right();
		turning_back = 0;
	}
	else if(right && !middle && !left)
	{
		bank_right();
		turning_back = 1;
	}
	else if (!turning_back)
	{
		bank_left();
	}




}

int iscrossing() { //TODO: make this work better
	return *(asense())<-lthreshold;
}


void turntoline () {
	//while(*(asense())<0-lsthreshold) controldrive(AUTOSPEED,0);
}
void driveincircle() {
	controldrive(-AUTOSPEED,AUTOSPEED);
}
void arc10(){//physical test for segment path navigation
	printf("test segment navigation2\n");
	delay(1000);
	int i=0;
	resetsegments();
	for(i=0;i<100;i++){
		segmentnav(SEG_FORWARD);	
		delay(50);
	}

	for(i=0;i<100;i++){
		segmentnav(SEG_LEFT_BANK);	
		delay(50);
	}
	undonav();

}
void aim(tank *v, int side) {
	int *ls=asense();
	while(*(ls+1)<-lthreshold){
		int turn;
		if(*(ls+2)<-lthreshold)
			turn=side;
		else
			turn=-side;
		controldrive(turn*AIMSPEED,0);
		delay(20);
		ls=asense();
	}
	v->h=(side*(PI/4));
	
}
void elf() {
	int bf=0;
	going=1;
	int linefollowing = S_SEKL;
	while(1) {

		if(linefollowing == S_SEKL)
		{
			int *ls=asense();
			int left = *(ls)<-lthreshold;
			int middle = *(ls+1)<-lthreshold;
			int right = *(ls+2)<-lthreshold;
			printf("%d %d %d\n",left,middle,right);
			if(left || middle || right)
			{
				linefollowing = S_FOLOW;
			}
			drive_straight();
		}
		else if(linefollowing == S_FOLOW)
		{
			elijah_linefollow();
			if(iscrossing()) {
				bf=10;
				linefollowing=S_BLIND;
			}
		}
		else if(linefollowing == S_BLIND)
		{
			bf=bf-1;
			printf("Ignoring sensors for %d iterations\n",bf);
			drive_straight();
			if(bf<=0)//should use encoders instead of loop iterations
				linefollowing = S_FOLOW;
		}

		analogRead(LS_LEFT);
		analogRead(LS_CENTER);
		analogRead(LS_RIGHT);
		asense();
		printf("%-6.0d%-6.0d%-6.0d%-6.0d%-6.0d%-6.0d\r\n", analogRead(LS_LEFT), analogRead(LS_CENTER), analogRead(LS_RIGHT), lss[0], lss[1], lss[2]);

		delay(20);

	}
	//TODO: end using range sensor

}
void suck(int speed) {//oposite of direction in opcontrol
	motorSet(MO_INTAKE,-speed);
}
void load(int speed) {

	motorSet(MO_CONVEYER1,speed);
}
void loadall(int speed) {
	int elapsed=0;
	const int limit =3000/10;
	motorSet(MO_CONVEYER1,speed);
	for(elapsed=0;elapsed<limit;elapsed++){
		controldrive(0,0);
		elapsed=elapsed+1;
		delay(10);
		printf("waited%d ",elapsed);
		if(!digitalRead(11))
		{
			printf("ball\n\r");
			break;
		}

	}
	motorSet(MO_CONVEYER1,0);
}

void shoot(int speed) {
	motorSet(MO_FLY1,speed);
	motorSet(MO_FLY2,-speed);
}
void autonomous() {
//	drivetogoal(&ltank);
	canned(); 
	wander();
	printf("done autonave\n\r");
}
