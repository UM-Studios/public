# Joining zoom meetings

This script will let you join a zoom link directly from terminal. 

## Instructions

You can download the file by clicking on it then clicking download. 

1. You first should add this script to your path. In your `.bashrc`/`.zshrc`/whatever else you may use, add `export PATH=$PATH:/PATH/TO/zoom.sh`
2. Anywhere in terminal, type `zoom.sh '<zoom link>'`

You need the single quotes there because otherwise terminal will interpret the link as a command, which unfortunaetly you really can't solve other than by using single quotes.

Pair this script with a dropdown terminal and it will save you "lots" of time (a couple clicks) every time you want to join a zoom meeting.

If you have a specific meeting code you often want to join, you can create an alias with that zoom link and this zoom script for even more speed.

## Customization

Edit the zoom.sh file to make it do whatever you want

## OS Compatability

At the moment, this script will only work on macos. However, with a little bit of tweaking it should work on linux, however I haven't gotten around to doing that yet. If you make this work on linux, please make a pull request so we can add it to this repo. Same with windows, except you might have to do a lot more tweaking there.
