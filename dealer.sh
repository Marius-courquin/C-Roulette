#!/bin/bash

# Launch the dealer which is locate in ./bin/server

if [ ! -e userStorage ]
then
    make
fi

clear
./bin/server