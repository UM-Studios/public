from googletrans import Translator
import pinyin
from PIL import Image
import pytesseract
import keyboard
import time
import os

def translit(to_trans):
  return pinyin.get(to_trans)

def translate(to_trans):
  translator = Translator()
  return(translator.translate(to_trans).text)

def take_sc():
  os.system('screencapture -i /tmp/translit.png')

def rm_sc():
  os.system('rm /tmp/translit.png')

def exec_translit():
  take_sc()
  to_trans = pytesseract.image_to_string(Image.open('/tmp/translit.png'), lang = 'chi_tra')
  print(translit(to_trans))
  rm_sc()

def exec_translate():
  take_sc()
  to_trans = pytesseract.image_to_string(Image.open('/tmp/translit.png'), lang = 'chi_tra')
  print(translate(to_trans))
  rm_sc()

keyboard.add_hotkey('f5', exec_translate)
keyboard.add_hotkey('f6', exec_translit)

while True:
  time.sleep(100000)

   