# Attend Your School's Zoom Meetings

This is a script to automatically join you into each of your period's zoom links at the correct time. 
*NOTE* If you move this directory around after running `install.sh`, you will have to rerun it.

## Instructions

1. If you do not have git, install it. In terminal, type `git --version`, and if it prompts you to install it, follow through.
2. Clone this repository. You will need a github account as well. If you don't know how to do that, open up terminal, and type
```
cd ~
mdkir -p src
cd src
git clone https://github.com/UM-Studios/public.git
cd public/SchoolZoomNoPopup
```
3. In terminal, type `./install.sh` and do what the script tells you to do. That's all!

## OS Compatibility

At the moment, this script will only work for MacOS, however with a bit of tweaking it should work for most Linux distros. It will take a lot of work to make it work on Windows.

## Customization

You can directly edit install.sh to change the format in which it gives you prompts. zoom.sh is just a script for opening zoom links.
