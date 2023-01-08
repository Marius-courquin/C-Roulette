#!/bin/bash

#Launch the player which is locate in ./bin/client with the argument $1 and $1 is the name of the player

if [ ! -e /dev/shm/sem.roulette-file ]
then
    echo "The dealer hasn't started to work yet ! Wait for him to start !"
    exit
fi

if [ $# -eq 0 ]
  then
    echo "You must enter your name in parameter of the command !"
    echo "Example: ./player.sh Magni"
    exit
else
    clear
    ./bin/client $1
fi

