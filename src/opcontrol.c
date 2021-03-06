/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
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
#include <API.h>
#include <../include/robot.h>
#include <main.h>
#include <auto.h>
#include <tank.h>
float a;
void stopdrive();
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
int dstat=1;
int leftspeed,rightspeed;
#define DONT_MOVE 0
void setmotors(){ 
	if(!DONT_MOVE){
	motorSet(MO_LEFT1,leftspeed);
	motorSet(MO_LEFT2,leftspeed);  
	motorSet(MO_RIGHT1,rightspeed);
	motorSet(MO_RIGHT2,rightspeed);
	}
}
void controldrive(int turn, int forward) {
	static int callcount=0;
	int lfly,rfly;
	if(callcount>10&&dstat==1) {
		printf("%d\t%d\t",turn,forward);
		printpos(&ltank);
		printball();
		printf("\n\r");
		imeGetVelocity(0,&lfly);
		imeGetVelocity(1,&rfly);
		printf("FLY SPEED: L %d\t R %d\n\r",lfly,rfly);
	//	printf("DIST:%d\t%d\n\r",encoderGet(r_encoder),encoderGet(l_encoder));
	//	non canned code
		simtank(&ltank,encoderGet(l_encoder),encoderGet(r_encoder));
		encoderReset(r_encoder);
		encoderReset(l_encoder);
	
		callcount=0;
	}

	callcount=callcount+1;
	leftspeed=forward;
	rightspeed=-1*forward;
	leftspeed+=turn;
	rightspeed+=turn;

	
	//simtank(&ltank,1,1);
	//TODO: encoders are degrees not radians
	setmotors();
}
int lfly=64;
int rfly=64;
/*
int controlbang(int target, int current) {

	//return (current<target-C_TOL) ? ((current>target+C_TOL) ? () : () ) :(target+C_BUMP); 
	int new;
	if(current < target-C_TOL)
		new=target+C_BUMP;
	else if(current > target+C_TOL)
		new=target-C_BUMP;
	return new;
}
int control(int target, int current, void *state){
	return controlbang(target, current);
}
//*/


void opdrive() {
	int joyforward = (abs(joystickGetAnalog(1,JOY_FORWARD)) > JOY_DEAD) ? joystickGetAnalog(1,JOY_FORWARD) : 0;//TODO: firgure out if this is cached or if we need to ourselves
	int joyturn = (abs((joystickGetAnalog(1,JOY_TURN))) > JOY_DEAD) ? joystickGetAnalog(1,JOY_TURN) : 0;
	controldrive(joyturn,joyforward);
}
void opconveyer() {
	
	int cs;

		//if(abs(joystickGetAnalog(1,JOY_INTAKE)) > JOY_DEAD) {
		if(abs(joystickGetDigital(1,JOY_INTAKE_B,JOY_UP))){
		//	motorSet(MO_INTAKE,joystickGetAnalog(1,JOY_INTAKE));
			cs=CONVEYER_SPEED;
		}else {
			if(joystickGetDigital(1,B_CONVEYER,JOY_DOWN) == true) {
				cs=-CONVEYER_SPEED;
			}else if(joystickGetDigital(1,B_CONVEYER,JOY_UP) == true) {
				cs=CONVEYER_SPEED;
			}else {
				cs=0;
			}

		}
		motorSet(MO_CONVEYER1,cs);
		
}
void opintake() {
	if(joystickGetDigital(1,JOY_INTAKE,JOY_UP) == true)
	{
		motorSet(MO_INTAKE,-MAX_SPEED);
	}
	else if (joystickGetDigital(1,JOY_INTAKE,JOY_DOWN) == true)
	{
		motorSet(MO_INTAKE,MAX_SPEED);
	}
	else
	{
		motorSet(MO_INTAKE,0);
	}
}

void drivestop() {
	leftspeed=0;
	rightspeed=0;
	setmotors();
}
void controlfly(int speed)
{
	if(!speed)
	{
		motorSet(MO_FLY1,0);
		motorSet(MO_FLY2,0);
		return;
	}

	int ltemp = lfly;
	int rtemp = rfly;

	imeGetVelocity(1,&lfly);
	imeGetVelocity(0,&rfly);

	printf("FLY SPEED: L %d\t R %d  go!\n\r",lfly,rfly);

	int adjustment = 1;

	if(lfly > -speed)
	{
		//printf("%d > %d decrease\n\r",lfly,-speed);
		//ltemp -= adjustment;
		ltemp = -128;
	}
	else if(lfly < -speed)
	{
		//ltemp += adjustment;
		ltemp = -40;
	}

	if(rfly > speed)
	{
		//rtemp -= adjustment;
		rtemp = 40;
	}
	else if(rfly < speed)
	{
		//printf("%d < %d increase\n\r",rfly,speed);
		//rtemp += adjustment;
		rtemp = 128;
	}

	lfly = ltemp;
	rfly = rtemp;

	printf("FLY POWER: L %d\t R %d  go!\n\r",lfly,rfly);

	motorSet(MO_FLY1,rtemp);//
	motorSet(MO_FLY2,ltemp);//
}
void opflywheel()
{
	//controlfly((joystickGetDigital(1,JOY_FLYWHEEL,JOY_UP) == true)*FLYCONTROLSPEED);
	//same as
	//*
	if(joystickGetDigital(1,JOY_FLYWHEEL,JOY_UP) == true)
	{
		controlfly(FLYHIGHSPEED);
	}
	else if(joystickGetDigital(1,JOY_FLYWHEEL,JOY_DOWN) == true)
	{
		controlfly(FLYCONTROLSPEED);
	}
	else
	{
		controlfly(0);
	}
	//*/
}
void opautotest() {//hook for quickly testing autonomous subnavigation
	if(joystickGetDigital(1,JOY_AUTOTEST_G,JOY_AUTOTEST_B)){
		encoderReset(l_encoder);
		encoderReset(r_encoder);
		ltank.x=0;
		ltank.y=0;
		ltank.h=0;
	}
	if(joystickGetDigital(1,JOY_AUTOTEST_G,JOY_TARGET)){
		printf("op_load_all\n\r");
		loadall(CONVEYER_SPEED);
	}
}

void print_us()
{
	static int callcount=0;
	if(callcount >10){
		printf("%40d \t%40d\n\r", ultrasonicGet(usL), ultrasonicGet(usR));
		callcount=0;
	}
	callcount +=1;
}
void operatorControl() {
	usR = ultrasonicInit(US_OUT_RIGHT, US_IN_RIGHT);
	usL = ultrasonicInit(US_OUT_LEFT, US_IN_LEFT);
	encoderReset(r_encoder);
	encoderReset(l_encoder);
	//autonomous();

	while (1)
	{

		opdrive();
		opintake();
		opconveyer();
		opflywheel();
		seeing_ball();
		opautotest();
		delay(20);

	}
}
