#!/usr/bin/env bash

if [[ ! -d venv ]]
then
    pip3 install virtualenv
    virtualenv venv 
    source venv/bin/activate
    pip install -r requirements.txt 
    deactivate
fi

source venv/bin/activate

echo "This script requires admin priviliges to run. If your computer prompts you, please type in your password to allow privilges. If you do not want to do this, press ctrl c"
sudo python translite.py

