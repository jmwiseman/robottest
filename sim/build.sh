#!/bin/bash
#TODO:makefile

echo Interactive simulation-----------------------------------------------------
cc -g -o isim ../src/opcontrol.c sim.c isim.c  -I ./
echo Static testing simulation-------------------------------------------------
cc -g -o testrobot ../src/opcontrol.c sim.c static.c -I ./

