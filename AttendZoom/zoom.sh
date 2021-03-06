#!/usr/bin/env bash

if ! open -Ra "zoom.us"
then
    echo "Please install zoom."
    exit 1
fi

if [ -z "$1" ]
then
    echo "Please enter a zoom link."
    exit 1
fi

if ! command -v ggrep &> /dev/null
then
    echo "Please install ggrep. i.e homebrew install grep"
    exit 1
fi

CONFNO=`echo "$1" | ggrep -oP '(?<=\/j\/)[0-9]*'`
PWD=`echo "$1" | ggrep -oP '(?<=pwd=)[0-9a-zA-Z]*'`

if [ ! -z "$PWD" ] 
then
    LINK="zoommtg://zoom.us/join?action=join&confno=$CONFNO&pwd=$PWD"
else
    LINK="zoommtg://zoom.us/join?action=join&confno=$CONFNO"
fi

open $LINK
