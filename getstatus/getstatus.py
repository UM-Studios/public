import tkinter as tk
from tkinter import *

import uiautomation as automation

import tkinter as tk

class UpdateLabel():
    def __init__(self):
        self.win = tk.Tk()
        self.vars()
        self.configTK()
        self.win.after(1000, self.updater)
        b = Button(self.win, text="end", command=self.exit)
        b.pack()
        self.win.wm_attributes("-topmost", 1)
        self.counter = 0
        self.win.mainloop()
    def exit(self):
        self.win.destroy()
    def configTK(self):
        self.win.title("Zoom Status")
        self.win.configure(bg='red')
    def vars(self):
        self.color = True
        self.inMeeting = False
        self.muted = False
        self.desktop = automation.GetRootControl()
        self.window = automation.WindowControl(searchDepth=1, ClassName='ZPContentViewWndClass')
        self.toolsMenu = self.window.WindowControl(searchDepth=3, ClassName='ZPControlPanelClass')
    def updater(self):
        print(f'before detect{self.counter}')
        self.DetectZoomMeeting()
        print(f'after detect{self.counter}{self.inMeeting}')
        if self.inMeeting:
            self.GetZoomStatus()

        if self.inMeeting:
            if self.muted:
                self.win.configure(bg='red')
            else:
                self.win.configure(bg='green')
        else:
            self.win.configure(bg='blue')
        print(f'{self.counter}')
        self.counter += 1
        self.win.after(500, self.updater)
        print(f'after{self.counter}')
    def GetFirstChild(self, control):
        return control.GetFirstChildControl()
    def GetNextSibling(self, control):
        return control.GetNextSiblingControl()
    def DetectZoomMeeting(self):
        for control, depth in automation.WalkTree(self.desktop, getFirstChild=self.GetFirstChild, getNextSibling=self.GetNextSibling, includeTop=False, maxDepth=2):
            if  str(control).find("ZPContentViewWndClass")  > 0 :
                self.inMeeting = True
                return
        self.inMeeting = False
    def GetZoomStatus(self):
        for control, depth in automation.WalkTree(self.toolsMenu, getFirstChild=self.GetFirstChild, getNextSibling=self.GetNextSibling, includeTop=False, maxDepth=2):
            if  str(control).find("currently muted")  > 0 :
                self.muted = True
            elif  str(control).find("currently unmuted")  > 0 :
                self.muted = False

UL=UpdateLabel()