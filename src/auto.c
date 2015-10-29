/** @file auto.c
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

#include "main.h"
#include "../include/robot.h"
#include "stdio.h"

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
#define lthreshold 20
void controldrive(int turn, int forward);
int *asense() {//NOT THREAD SAFE
	int als=0;
	int ls[3];
	int i=0;
	ls[0]=analogRead(LS_LEFT);
	ls[1]=analogRead(LS_CENTER);
	ls[2]=analogRead(LS_RIGHT);
	int average=(ls[0]+ls[1]+ls[2])/3;
	for( i=0; i<3;i++){
			lss[i]=ls[i]-average;
	}

	return &lss[0];
}

void simple_linefollow() {
	int sensed=asense();
	if(sensed && LS_B_L) {
		controldrive(AUTOSPEED,AUTOSPEED);
	}
	if(sensed && LS_B_R) {
			controldrive(-AUTOSPEED,AUTOSPEED);
	}
	if(sensed && LS_B_C) {
			controldrive(AUTOSPEED,AUTOSPEED);
	}
}
void turntoline () {
	//while(*(asense())<0-lsthreshold) controldrive(AUTOSPEED,0);
}
void autonomous() {
	while(1) {
		printf("Sensor value: %d ",analogRead(LS_LEFT));
		//printf("Sensor value: %d\n",analogRead(LS_LEFT));
		turntoline();
		simple_linefollow();
		analogRead(LS_LEFT);
		analogRead(LS_CENTER);
		analogRead(LS_RIGHT);

		printf(" OS yeild\n");
		delay(20);
	}

}
