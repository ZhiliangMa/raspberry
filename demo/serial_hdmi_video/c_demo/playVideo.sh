#!/bin/bash

name=$1
name=`echo $1|awk '{printf("%04d\n",$0)}'`
echo "/home/pi/$name.mp4"

omxplayer -o hdmi /home/pi/$name.mp4 --loop
#omxplayer -o hdmi /home/pi/DJI-MAVIC-AIR2.mp4 --loop
