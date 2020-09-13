from googletrans import Translator
from PIL import Image
import pytesseract
import keyboard
import time
import os
import pyautogui as pya
import pyperclip
from PyQt5.QtWidgets import QApplication, QLabel
from PyQt5.QtCore import Qt

os.system('rm translites.txt; touch translites.txt')

app = QApplication([])

label = QLabel('Close me when you done')
  
flags = Qt.WindowFlags(Qt.WindowStaysOnTopHint)
label.setWindowFlags(flags)

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
    to_trans = pytesseract.image_to_string(Image.open('/tmp/translit.png'), lang='chi_sim')
    return to_trans


def show_res(text):
    text = str(text)
    label.setText(text)
    os.system(f'echo "{text}" >> translites.txt')
    label.raise_()


def exec_translit():
    take_sc()
    to_trans = ocr()
    to_trans = translit(to_trans)
    show_res(to_trans)
    rm_sc()


def exec_translate():
    take_sc()
    to_trans = ocr()
    to_trans = translate(to_trans)
    show_res(to_trans)
    rm_sc()


def exec_cpy_translit():
    text = copy_clipboard()
    text = translit(text)
    show_res(text)


def exec_cpy_translate():
    text = copy_clipboard()
    text = translate(text)
    show_res(text)


keyboard.add_hotkey('f6', exec_translate)
keyboard.add_hotkey('f5', exec_translit)
keyboard.add_hotkey('command+f6', exec_cpy_translate)
keyboard.add_hotkey('command+f5', exec_cpy_translit)

label.show()

app.exec_()

