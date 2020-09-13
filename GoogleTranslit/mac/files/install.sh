#!/usr/bin/env bash

which -s brew
if [[ $? != 0 ]]
then
    echo "This script will need to install homebrew. If you are unsure what homebrew is, you can get a quick overview here: https://techstacker.com/what-is-homebrew/. If you will allow this script to install homebrew, type yes. Otherwise, type no. [yes/no]"

    while [[ true ]]
    do
        read agree
        if [[ $agree == "no" ]]
        then
            exit 0
        elif [[ $agree == "yes" ]]
        then
            break
        else
            echo "Please enter yes or no."
        fi

    done
    if /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
    then
        echo "Installed homebrew successfully"
    else
        echo "Oops! looks like something went wrong with the download. Please read the error message and try to download homebrew yourself. Or, restart this script and see if it works then."
        exit 1
    fi
    printf '\n\n\n\n'
fi

brew install python
brew install tesseract
brew install wget


while IFS=, read -r code name; do
  wget https://github.com/tesseract-ocr/tessdata_best/raw/master/$code.traineddata
  mv $code.traineddata /usr/local/share/tessdata
done < language_codes.csv

echo "All done! Please restart terminal before running the program. To run, type ./run.sh -S for simplified or ./run.sh -T for traditional"