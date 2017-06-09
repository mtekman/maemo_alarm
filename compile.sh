#!/bin/bash

target=alarum
lib="-lalarm"
extra="${@:1}"

g++ -o $target src/{main.cc,timeops.h,alarmcookie.h,arghandler.h,recur.h} $lib $extra
