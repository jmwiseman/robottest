#!/bin/bash

./build.sh
echo running tests
ln -s ../include/robot.h ./ #this is the wrong thing to do but Im doing it anyway because its easy
./testrobot >./testlog.txt
echo done

