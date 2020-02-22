#!/bin/bash
make
time ./run $1 $2
make clean
