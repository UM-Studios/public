# Translate Screenshot

This script allows you to take screenshots of or highlight any text in any (most) languages, and it will give you the text's translation and pronunciation.. If you're struggling in Chinese class like one of our members is, this will be a very useful script for you (along with [Google Translit](https://github.com/UM-Studios/public/tree/master/GoogleTranslit))

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

4. Once you are done running the install script, you will have to restart your terminal (quitting and reopening terminal). After restarting terminal, we will first have to get back inside the file folder, then you can set the language you want to be able to screenshot. In terminal, type
```
cd ~/src/files
./set_lang.py -h
```
This will bring up the help menu and display all the language codes. Then, you can use those language codes to set whatever language you would like it to read. For example, if you wanted to set it to read traditional chinese, you would type `./set_lang.py --lang chi_tra` in terminal.

5. Now, you are ready to run the program. To run it, we will need to run the run.sh script. In terminal, type
```
cd ~/src/files
./run.sh
```
This will do some one time installations and run the program. The default language the screenshotting can read it chinese simplified.

6. To use this program, run the run.sh script and press f5 to translate a screenshot and f6 to give you the text you screenshotted's pronunciation, but it can only read the language you specified. Alternatively, you can highly text and press cmd f5(it may only work with the right cmd key) to translate text you highlighted or cmd f6 to give you the pronuncation of the text you highlighted. The results will be shown in a popup window. DO NOT CLOSE THIS WINDOW. If you close the window, the program will stop and you will have to run it again. 

7. When you are done, close the popup window.

## Customization

To customize the hotkey triggers, you will need to edit the translite.py file. On lines 88-91, you will see code similar to `keyboard.add_hotkey('f6', exec_translate)`.These lines control the hotkeys. Line 88 controls screenshot translation, 89 controls screenshot pronunciation, 90 controls highlighted text tranlsation, and 91 controls highlighted text pronunciation. To set custom hotkeys, replace 'f6' with whatever key combinations you like. 
To change it, replace f5 with whatever key combination you want. For example, if you want translate to trigger on space, replace `'f5'` with `' '`, or if you want pinyin to trigger on control-u, replace `'f6'` with `'ctrl+u'`. 

## OS Compatability

This script will only work on MacOS. For Windows, look at [Google Translit](https://github.com/UM-Studios/public/tree/master/GoogleTranslit) which will be adding the screenshot feature shortly. If you make this script work on any other OS, please submit a pull request so we can add it to this repo.
