import os
import re
from datetime import datetime
from json import JSONEncoder
import json
from pathlib import Path

day_to_num = {
  'monday': 1,
  'tuesday': 2,
  'wednesday': 3,
  'thursday': 4,
  'friday': 5,
  'saturday': 6,
  'sunday': 7
}

open_script = '''#!/usr/bin/env bash

open '[link]'
'''


class TaskEncoder(JSONEncoder):
  def default(self, o):
    if hasattr(o, 'reprJSON'):
      return o.reprJSON()
    else:
      return json.JSONEncoder.default(self, o)

class Task():

  def __init__(self, name, minute, hour, day_of_week, link):
    self.enabled = True
    self.name = name
    self.link = link
    self.minute = minute
    self.hour = hour
    self.day_of_week = day_of_week

  def create_file(self):
    confno = re.compile(r'(?<=\/[a-zA-Z]\/)[0-9]*').search(self.link)
    token = re.compile(r'(?<=tk=)[0-9a-zA-Z\-_\.]*').search(self.link)
    password = re.compile(r'(?<=pwd=)[0-9a-zA-Z]*').search(self.link)

    if confno != None:
      confno = f'&confno={confno.group(0)}'

    if token == None:
      token = ''
    else:
      token = f'&tk={token.group(0)}'

    if password == None:
      password = ''
    else:
      password = f'&pwd={password.group(0)}'

    post_link = f'zoommtg://zoom.us/join?action=join{confno}{token}{password}'
    new_open_script = open_script.replace('[link]', post_link)

    os.system(f'cd ~/.createzoom; touch zoomOpen{self.name}.sh; echo "{new_open_script}" > zoomOpen{self.name}.sh; chmod 700 zoomOpen{self.name}.sh')
  
  def schedule_cron(self):
    os.system('crontab -l > mycron')

    self.cron = f'{self.minute} {self.hour} * * {self.day_of_week} cd {str(Path.home())} && bash -lc {str(Path.home())}/.createzoom/zoomOpen{self.name}.sh'
    os.system(f'echo "{self.cron}" >> mycron')
    
    os.system('crontab mycron; rm mycron')

  def add_task(self):
    all_tasks = self.get_all_tasks()
    print(all_tasks)
    all_tasks.append(self.reprJSON())
    with open(f'{str(Path.home())}/.createzoom/tasks.json', 'w') as f:
      json.dump(all_tasks, f, cls = TaskEncoder)
    
  def delete_task(self):
    os.system('crontab -l > mycron')
    with open('mycron', 'r') as f:
      crons = f.readlines()
    if self.enabled:
      crons.remove(self.cron + '\n')
    os.system('rm mycron; touch mycron')
    for cron in crons:
      os.system(f'echo "{cron}" >> mycron')
    os.system('crontab mycron; rm mycron')
    all_tasks = self.get_all_tasks()
    all_tasks.remove(self.reprJSON())
    with open(f'{str(Path.home())}/.createzoom/tasks.json', 'w') as f:
      json.dump(all_tasks, f, cls = TaskEncoder)
    os.system(f'cd ~/.createzoom; rm zoomOpen{self.name}.sh')
  
  def edit_task(self, enabled = None, name = None, link = None, minute = None, hour = None, day_of_week = None):
    self.delete_task()
    if enabled != None:
      self.enabled = enabled
    if name:
      self.name = name
    if link:
      self.link = link
    if minute:
      self.minute = minute
    if hour:
      self.hour = hour
    if day_of_week:
      self.day_of_week = day_of_week
    self.create_file()
    self.add_task()
    if self.enabled:
      self.schedule_cron()
    
  def reprJSON(self):
    return dict(enabled = self.enabled, name = self.name, link = self.link, minute = self.minute, hour = self.hour, day_of_week = self.day_of_week)

  @classmethod
  def get_all_tasks(cls):
    with open(f'{str(Path.home())}/.createzoom/tasks.json') as f:
      all_tasks = json.loads(f.read())
    return all_tasks




