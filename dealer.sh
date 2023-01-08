#!/bin/bash

# Launch the dealer which is locate in ./bin/server

#check if server file exist if not make it
if [ ! -e ./bin/server ]
then
    make
fi

clear
./bin/server