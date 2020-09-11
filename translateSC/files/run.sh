#!/usr/bin/env bash

if [[ ! -d venv ]]
then
  pip3 install virtualenv
  virtualenv venv 
  source venv/bin/activate
  pip install -r requirements.txt
  deactive
  cp chi_tra.traineddata /usr/local/share/tessdata
  cp chi_sim.traineddata /usr/local/share/tessdata
fi

source venv/bin/activate

echo "This script requires admin priviliges to run. Please type in your password to allow privilges. If you do not want to do this, press ctrl c"

if [[ $1 -eq 1 ]]
then
    sudo python translit_simp.py
elif [[ $1 -eq 2 ]]
then
    sudo python translit_trad.py
fi
