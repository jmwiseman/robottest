#!/bin/bash
#TODO:makefile
cp ../include/robot.h ./
echo Building autonomous simulation-----------------------------------------------------
cc -o testauto ../src/opcontrol.c ../src/auto.c sim.c tank.c  -I ./
./testauto

