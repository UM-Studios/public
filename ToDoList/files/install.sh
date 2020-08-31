#!/usr/bin/env bash

TODO="alias todo=$PWD/dist/todo.app/Contents/MacOS/todo"

if [[ -f "$HOME/.bashrc" ]]
then
    echo $TODO >> $HOME/.bashrc
elif [[ -f "$HOME/.bash_profile" ]]
then
    echo $TODO >> $HOME/.bash_profile
elif [[ -f "$HOME/.zshrc" ]]
then
    echo $TODO >> $HOME/.zshrc
elif [[ -f "$HOME/.zsh_profile" ]]
then
    echo $TODO >> $HOME/.zsh_profile
elif [[ -f "$HOME/.profile" ]]
then
    echo $TODO >> $HOME/.profile
else
    echo "Couldn't find a .profile or any of its variatins. To manally set up, please put this line"
    echo $TODO
    echo "in your .bashrc/whatever you use, and then source the file."
fi

echo "You should be all set up! The final step is to restart your terminal so the aliases take effect. To use this script, type todo -h in terminal to get a list of commands."
echo "Thank you for using UM Studio's todo list script. To keep up with our content, follow us at @_umstudios_ on instagram. Thanks!"