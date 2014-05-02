#!/bin/bash

target=alarum
lib="-lalarm"
extra="${@:1}"

g++ -o $target main.cc timeops.h alarmcookie.h arghandler.h $lib $extra
