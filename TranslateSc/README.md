# Translate Screenshot

This script allows you to take screenshots of both traditional or simplified text and have it give you the translation or pinyin. If you're struggling in Chinese class like one of our members is, this will be a very useful script for you (along with [Google Translit](https://github.com/UM-Studios/public/tree/master/GoogleTranslit))

## Instructions

1. You can download the files.zip filer by clicking on it then clicking download. Leave files.zip in the downloads folder for the time being.
2. We will now need to use terminal. Open up terminal and type in (or copy paste)
```
cd ~
mkdir -p src
cd src
mv ~/Downloads/files.zip .
unzip files.zip
```
This will move the files.zip folder into a newly (or not) created src folder and unzips it.

3. Next, we will run the install script. In terminal, type in
```
cd files
./install.sh
```
Follow the instructions it gives you.

4. Once you are done running the install script, you will have to restart your terminal. After restarting terminal, we will first have to get back inside the file folder, then you can run the run.sh script. In terminal, type
```
cd ~/src/files
./run.sh -H
```
This will do some one time installations and bring up the help menu. From there, follow the instructions it gives you.

5. To use this program, run the run.sh script and press f5 to translate a screenshot and f6 to give you pinyin. The results will be shown on terminal, so make sure to keep an eye on it! We highly recommend you use this with a dropdown terminal, which you can set up [here](https://www.sharmaprakash.com.np/guake-like-dropdown-terminal-in-mac/).

## Customization

To customize the hotkey triggers, you will need to edit the translit_trad.py or translit_simp.py, depending on whether you use traditional or simplified. On lines 34 and 35, you should see `keyboard.add_hotkey('f5', exec_translate)` and `keyboard.add_hotkey('f6', exec_translit)` respectively. Line 34 controls the translate hotkey, which is set to f5 by default, and 35 controls the translit hotkey which is set to f6 automatically.
To change it, replace f5 with whatever key combination you want. For example, if you want translate to trigger on space, replace `'f5'` with `' '`, or if you want pinyin to trigger on control-u, replace `'f6'` with `'ctrl+u'`. 

## OS Compatability

This script will only work on MacOS. For Windows, look at [Google Translit](https://github.com/UM-Studios/public/tree/master/GoogleTranslit) which will be adding the screenshot feature shortly. If you make this script work on any other OS, please submit a pull request so we can add it to this repo.
