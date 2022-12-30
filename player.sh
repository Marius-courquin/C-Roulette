#!/bin/bash

#Launch the player which is locate in ./bin/client with the argument $1 and $1 is the name of the player

if [ $# -eq 0 ]
  then
    echo "You must enter your name in parameter of the command !"
    echo "Example: ./player.sh Magni"
    exit
fi

if [ -e userStorage ]
then
    clear
    ./bin/client $1
else
    echo "The dealer hasn't started to work yet ! Wait for him to start !"
fi
