from googletrans import Translator
import pinyin
from PIL import Image
import pytesseract
import keyboard
import time
import os
import pyautogui as pya
import pyperclip
import tkinter as tk
from tkinter import ttk


def translit(to_trans):
    return pinyin.get(to_trans)


def translate(to_trans):
    translator = Translator()
    return (translator.translate(to_trans).text)


def copy_clipboard():
    original = pyperclip.paste()
    pya.hotkey('command', 'c')
    time.sleep(0.05)
    text = pyperclip.paste()
    pyperclip.copy(original)
    return text


def take_sc():
    os.system('screencapture -i /tmp/translit.png')


def rm_sc():
    os.system('rm /tmp/translit.png')


def exec_translit():
    take_sc()
    try:
        Image.open('/tmp/translit.png')
    except:
        print('u are a nerd')
        return
    to_trans = pytesseract.image_to_string(Image.open('/tmp/translit.png'), lang='chi_tra')
    print(translit(to_trans))
    rm_sc()


def exec_translate():
    take_sc()
    try:
        Image.open('/tmp/translit.png')
    except:
        print('u are a dumbass')
        return
    to_trans = pytesseract.image_to_string(Image.open('/tmp/translit.png'), lang='chi_tra')
    print(translate(to_trans))
    rm_sc()


def exec_cpy_translit():
    text = copy_clipboard()
    print(translit(text))


def exec_cpy_translate():
    text = copy_clipboard()
    print(translate(text))


keyboard.add_hotkey('f6', exec_translate)
keyboard.add_hotkey('f5', exec_translit)
keyboard.add_hotkey('command+f6', exec_cpy_translate)
keyboard.add_hotkey('command+f5', exec_cpy_translit)

while True:
    time.sleep(100000)
