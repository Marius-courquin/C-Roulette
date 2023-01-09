#! /bin/bash

# This script is used to setup the environment for the C-ROULETTE

player_username="player"
player_password="roulette"

echo "--------------------------------------------------------------------------------"
echo "Setting up the environment for C-ROULETTE"
echo "--------------------------------------------------------------------------------"

echo "Creating the player user"
egrep "^player" /etc/passwd >/dev/null
if [ $? -eq 0 ]; then   
    echo "User player already exist"
else
    password=$(perl -e 'print crypt($ARGV[0], "password")' $player_password)
    useradd -s /bin/bash -m -p "$password" "$player_username"
    if [ $? -ne 0 ]; then
        echo "Player account created"
    fi
    echo "Adding alias PLAY"
    echo "alias PLAY='cd /home/ubuntu/C-Roulette;./player.sh'" >> /home/player/.bashrc
fi
echo "--------------------------------------------------------------------------------"

echo "Setup script done"

./dealer.sh

echo "You can now use the command 'PLAY yourname' to start playing !"