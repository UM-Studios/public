#!/usr/bin/env bash

if [[ ! -d venv ]]
then
    pip3 install virtualenv
    virtualenv venv 
    source venv/bin/activate
    pip install -r requirements.txt
    deactivate
    cp chi_tra.traineddata /usr/local/share/tessdata
    cp chi_sim.traineddata /usr/local/share/tessdata
fi

source venv/bin/activate

if [[ getopts ]]
then
    echo "use ./run.sh -T for traditional or ./run.sh -S for simplified. For help, do ./run.sh -H"
fi

while getopts "TSH" FLAG
do
    case $FLAG in
        T)
            echo "This script requires admin priviliges to run. If your computer prompts you, please type in your password to allow privilges. If you do not want to do this, press ctrl c"
            sudo python translite_trad.py
            ;;
        S)
            echo "This script requires admin priviliges to run. If your computer prompts you, please type in your password to allow privilges. If you do not want to do this, press ctrl c"
            sudo python translite_simp.py
            ;;
        H)
            echo "Press f5 to take a screenshot of chinese text and get the translation of the text you screenshotted. Press f6 to take a screenshot of chinese text and get the text's pinyin.
Use ./run.sh -T for traditional text and ./run.sh -S for simplified text."
            ;;
        *)
            echo "use ./run.sh -T for traditional or ./run.sh -S for simplified. For help, do ./run.sh -H"
            ;;
    esac
done

