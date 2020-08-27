#!/usr/bin/env bash

LINKS=( `jq -r .[] $PWD/links.json` )
PRE_LINK=${LINKS[$1 - 1]}

CONFNO=`echo $PRE_LINK | ggrep -oP '(?<=\/[a-zA-Z]\/)[0-9]*'`
PASSWORD=`echo $PRE_LINK | ggrep -oP '(?<=pwd=)[0-9a-zA-Z]*'`
TOKEN=`echo $PRE_LINK | ggrep -oP '(?<=tk=)[0-9a-zA-Z\-_.]*'`

if [ ! -z "$CONFNO" ]
then
    CONFNO="confno=$CONFNO"
fi

if [ ! -z "$PASSWORD" ]
then
    PASSWORD="&pwd=$PASSWORD"
fi

if [ ! -z "$TOKEN" ]
then
    TOKEN="&tk=$TOKEN"
fi

POST_LINK="zoommtg://zoom.us/join?action=join&$CONFNO$PASSWORD$TOKEN"

open $POST_LINK
