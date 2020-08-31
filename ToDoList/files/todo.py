import json
import argparse
import os
import os.path
from os import path
from pathlib import Path

def get_todo():
  home = str(Path.home())
  os.system(f'mkdir -p {home}/.todo')
  if not path.exists(f'{home}/.todo/todo.json'):
    os.system(f'touch {home}/.todo/todo.json; echo "[]" > {home}/.todo/todo.json')
  with open(f'{home}/.todo/todo.json') as f:
    todo = json.load(f)
    return todo

def write_todo(todo):
  home = str(Path.home())
  os.system(f'mkdir -p {home}/.todo')
  if not path.exists(f'{home}/.todo/todo.json'):
    os.system(f'touch {home}/.todo/todo.json; echo "[]" > {home}/.todo/todo.json')
  with open(f'{home}/.todo/todo.json', 'w') as f:
    json.dump(todo, f)

def list_elem():
  todo = get_todo()
  for i in range(len(todo)):
    print(f'{i}: {todo[i]}')

def remove(idx):
  todo = get_todo()
  if idx < 0 or idx >= len(todo):
    print('Please provide a valid index to remove.')
    return
  todo.pop(idx)
  write_todo(todo)
  todo = get_todo()
  list_elem()

def add(task):
  todo = get_todo()
  todo.append(task)
  write_todo(todo)
  todo = get_todo()
  list_elem()

parser = argparse.ArgumentParser(description='Add, Remove, and List things in a todo list.')
parser.add_argument('-a', '--add', dest='add', type=str, help='-a "[message]" adds [message] to your todo list (note the double quotes around [message])')
parser.add_argument('-r', '--remove', dest='remove', type=str, help='-r [number] removes the message at index [number] from your todo list')
parser.add_argument('-l', '--list', action='store_true', help='-l lists your todo lists all messages and their indices')

try:
  args = parser.parse_args()
  if args.list:
    list_elem()
  if args.add:
    add(args.add)
  if args.remove:
    remove(int(args.remove))
except:
  print('Please enter correct arguments. See --help for a list of arguments')

