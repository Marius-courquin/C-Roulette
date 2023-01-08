#!/bin/bash

# Launch the dealer which is locate in ./bin/server

#check if server file exist if not make it
if [ ! -e ./bin/server ]
then
    make
fi


clear

if [ ! -e /dev/shm/sem.roulette-file ]
then
    ./bin/server
else 
    echo "The dealer is already working !"
fi