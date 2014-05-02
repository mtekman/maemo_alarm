#!/bin/bash
[ "$1" = "" ] && echo "give arg" && exit -1


if [[ "$1" =~ "list" ]]; then
	./alarum list
else
	./alarum /opt/cloudgps/cloudgps $1
fi
