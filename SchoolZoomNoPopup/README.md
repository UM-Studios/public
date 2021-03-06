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
Alternatively, you can paste the folder url [here](https://kinolien.github.io/gitzip/) and click download to download the repository as a zip file.

Once you have cloned or unzipped the colder, type `./install.sh` in terminal and do what the script tells you to do. That's all!


## Customization

You can directly edit install.sh to change the format in which it gives you prompts. zoom.sh is just a script for opening zoom links.

## OS Compatability

Currently, this script will only work on MacOS. However, with a little bit of tweaking, such as removing the ggrep check and changing `open` to `xdg-open`, it should not be too difficult to make this work on Linux. Unless you completely rewrote this in batch, this script will not work on Windows. If you make this script work on any other OS, please submit a pull request so we can add it to this repo.
