#!/usr/bin/env bash

LINKS=( `jq -r .[] $PWD/links.json` )
PRE_LINK=${LINKS[$1 - 1]}
echo $1
CONFNO=`echo $PRE_LINK | ggrep -oP '(?<=\/j\/)[0-9]*'`
PASSWD=`echo $PRE_LINK | ggrep -oP '(?<=pwd=)[0-9a-zA-Z]*'`

if [ ! -z "$PWD" ]
then
    POST_LINK="zoommtg://zoom.us/join?action=join&confno=$CONFNO&pwd=$PASSWD"
else
    POST_LINK="zoommtg://zoom.us/join?action=join&confno=$CONFNO"
fi

open $POST_LINK
