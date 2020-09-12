from googletrans import Translator
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
    translator = Translator()
    return translator.translate(to_trans).translit


def translate(to_trans):
    translator = Translator()
    return translator.translate(to_trans).text


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


def ocr():
    try:
        Image.open('/tmp/translit.png')
    except:
        print('u are a nerd')
        return
    to_trans = pytesseract.image_to_string(Image.open('/tmp/translit.png'), lang='chi_tra')
    return to_trans


def exec_translit():
    take_sc()
    to_trans = ocr()
    to_trans = translit(to_trans)
    print(to_trans)
    rm_sc()


def exec_translate():
    take_sc()
    to_trans = ocr()
    to_trans = translate(to_trans)
    print(to_trans)
    rm_sc()


def exec_cpy_translit():
    text = copy_clipboard()
    text = translit(text)
    print(text)


def exec_cpy_translate():
    text = copy_clipboard()
    text = translate(text)
    print(text)


keyboard.add_hotkey('f6', exec_translate)
keyboard.add_hotkey('f5', exec_translit)
keyboard.add_hotkey('command+f6', exec_cpy_translate)
keyboard.add_hotkey('command+f5', exec_cpy_translit)

while True:
    time.sleep(100000)
