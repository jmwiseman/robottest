#!/bin/bash
#TODO:makefile

echo Interactive simulation-----------------------------------------------------
cc -o isim ../src/opcontrol.c sim.c isim.c  -I ./
echo Static testing simulation-------------------------------------------------
#cc -o test ../src/opcontrol.c sim.c static.c test.c -I ./

