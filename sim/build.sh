#!/bin/bash
#TODO:makefile

echo Interactive simulation-----------------------------------------------------
cc -o isim ../src/opcontrol.c sim.c isim.c  -I ./
echo Static testing simulation-------------------------------------------------
cc -o testrobot ../src/opcontrol.c sim.c static.c -I ./

