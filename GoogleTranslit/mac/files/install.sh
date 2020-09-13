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

echo "This script needs to install data files for our screenshot character recognition to work. Would you like to install better data for higher accuracy but longer download times, or faster data for less accuracy but faster download times? Type better for better data or faster for faster data [better/faster]"

while [[ true ]]
do
  read which_data
  if [[ $which_data == "better" ]]
  then
    data="best"
    break
  elif [[ $which_data == "faster" ]]
  then
    data="fast"
    break
  else
    echo "Please enter either better or faster"
  fi
done

wget_out=$(wget https://github.com/tesseract-ocr/tessdata_$data/archive/master.zip)
if [[ $? -ne 0 ]]
then
  echo "Oops look like something went wrong. Look through the error message to find out, or run this script again and see if it works."
  exit 1
fi

unzip master.zip
mv tessdata_$data-master/*.traineddata /usr/local/share/tessdata
rm master.zip
rm -rf tessdata_$data-master

echo "All done! Please restart terminal before running the program."