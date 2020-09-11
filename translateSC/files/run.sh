#!/usr/bin/env bash

source venv/bin/activate

echo "This script requires admin priviliges to run. Please type in your password to allow privilges. If you do not want to do this, press ctrl c"

if [[ $1 -eq 1 ]]
then
    sudo python translit_simp.py
elif [[ $1 -eq 2 ]]
then
    sudo python translit_trad.py
fi
