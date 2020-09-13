#!/usr/bin/env python3

import csv
import sys
import argparse
import os

lang_codes = []

with open('language_codes.csv', newline='') as csvfile:
  spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
  for row in spamreader:
    lang_codes.append([row[0].split(',')[0], row[0].split(',')[1]])

def show_help():
  ret = ''
  ret += 'The language code of the language you want to translate. \nHere are the language codes:\n'
  for lang in lang_codes:
    ret += f'{lang[0]}: {lang[1]}\n'
  return ret

lang_help = show_help()

parser = argparse.ArgumentParser(description = 'Set the language for your screenshot translations.', formatter_class = argparse.RawTextHelpFormatter)
parser.add_argument('-l', '--lang', dest = 'lang', required = True, type = str, help = lang_help)

args = parser.parse_args()

lang = args.lang

if all(lang not in l for l in lang_codes):
  print('Please use a valid language code. To get a list of language codes and the language they map to, do ./set_lang -h')
else:
  sed_1 = f"s/\(lang='.*'\)/lang='{lang}'/g"
  os.system(f'sed "{sed_1}" translite.py > temp.txt; mv temp.txt translite.py')
  print(f'Successfully changed language to {lang}!')