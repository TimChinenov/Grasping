#!/bin/bash
g++ -std=c++11 -I/usr/include/python2.7 -I/usr/include/eigen3  main.cpp node.cpp obs.cpp -lpython2.7 -o test
drmemory -brief -- a.out
