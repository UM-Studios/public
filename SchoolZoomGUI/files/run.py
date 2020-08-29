import tkinter as tk
from tkinter import ttk
from tkinter.messagebox import showinfo

def popup_edit():
  showinfo("Window", "Hello World!")

class Application(ttk.Frame):

  def __init__(self, master):
    
    master.geometry("500x400")
    master.wm_title('Zoom Scheduler')

    ttk.Frame.__init__(self, master)
    self.pack()
    self.default_window()

  def default_window(self):
    self.head_text_style = ttk.Style(self)
    self.head_text_style.configure("HeadText.TLabel", font = ('Helvetica', 24))
    self.head_text = ttk.Label(self, text="Zoom Scheduler by UM Studios", style = "HeadText.TLabel")
    self.head_text.grid(row = 1, pady = 20)
    self.head_text.columnconfigure(0, weight = 1)

    self.button_schedule = ttk.Button(self, text="Schedule zoom", command=self.popup_schedule)
    self.button_schedule.grid(row = 2, pady = 10)
    self.button_schedule.columnconfigure(0, weight = 1)

    self.button_edit = ttk.Button(self, text="Edit tasks", command=popup_edit)
    self.button_edit.grid(row = 3)
    self.button_edit.columnconfigure(0, weight = 1)

  def click_day(self, day):
    print(day)
    # if day == 'monday':
    #   self.monday_canvas.itemconfig(self.monday_canvas_rect, fill = '#41A0F0')
    # else:
    #   self.monday_canvas.itemconfig(self.monday_canvas_rect, fill = '#E2E2E2')
    # if day == 'tuesday':
    #   self.tuesday_canvas.itemconfig(self.tuesday_canvas_rect, fill = '#41A0F0')
    # else:
    #   self.tuesday_canvas.itemconfig(self.tuesday_canvas_rect, fill = '#E2E2E2')
    # if day == 'wednesday':
    #   self.wednesday_canvas.itemconfig(self.wednesday_canvas_rect, fill = '#41A0F0')
    # else:
    #   self.wednesday_canvas.itemconfig(self.wednesday_canvas_rect, fill = '#E2E2E2')
    # if day == 'thursday':
    #   self.thursday_canvas.itemconfig(self.thursday_canvas_rect, fill = '#41A0F0')
    # else:
    #   self.thursday_canvas.itemconfig(self.thursday_canvas_rect, fill = '#E2E2E2')
    # if day == 'friday':
    #   self.friday_canvas.itemconfig(self.friday_canvas_rect, fill = '#41A0F0')
    # else:
    #   self.friday_canvas.itemconfig(self.friday_canvas_rect, fill = '#E2E2E2')
    # if day == 'saturday':
    #   self.saturday_canvas.itemconfig(self.saturday_canvas_rect, fill = '#41A0F0')
    # else:
    #   self.saturday_canvas.itemconfig(self.saturday_canvas_rect, fill = '#E2E2E2')
    # if day == 'sunday':
    #   self.sunday_canvas.itemconfig(self.sunday_canvas_rect, fill = '#41A0F0')
    # else:
    #   self.sunday_canvas.itemconfig(self.sunday_canvas_rect, fill = '#E2E2E2')

  def select_monday(self, event = None):
    self.click_day('monday')
    
  def select_tuesday(self, event = None):
    self.click_day('tuesday')
  
  def select_wednesday(self, event = None):
    self.click_day('wednesday')
  
  def select_thursday(self, event = None):
    self.click_day('thursday')
  
  def select_friday(self, event = None):
    self.click_day('friday')
  
  def select_saturday(self, event = None):
    self.click_day('saturday')

  def select_sunday(self, event = None):
    self.click_day('sunday')

  def popup_schedule(self):
    self.win = tk.Toplevel()
    self.win.wm_title("Schedule Zoom Task")

    self.meeting_name = ttk.Label(self.win, text = "Meeting Name:")
    self.meeting_input = ttk.Entry(self.win)
    self.meeting_name.grid(row = 1, sticky = 'W', padx = 5, pady = (5, 0))
    self.meeting_input.grid(row = 2, padx = 5)

    self.paste_zoom = ttk.Label(self.win, text = "Paste Zoom link:")
    self.zoom_input = ttk.Entry(self.win)
    self.paste_zoom.grid(row = 3, sticky = 'W', pady = (5, 0), padx = 5)
    self.zoom_input.grid(row = 4, padx = 5)

    self.select_day = ttk.Label(self.win, text = "Select Day:")
    self.select_day.grid(row = 5, sticky = 'W', pady = (5, 0), padx = 5)

    self.monday_canvas = tk.Canvas(self.win, width = 100, height = 140)
    self.background_rect = self.monday_canvas.create_rectangle(0, 0, 99, 139, fill = "#E2E2E2", outline = "#000000")
    self.monday_canvas_rect = self.monday_canvas.create_rectangle(0, 0, 99, 20)
    self.monday_canvas.create_text((5, 10), text = "Monday", fill = "#111111", anchor = 'w')
    # self.monday_canvas_rect.bind("<Button-1>", self.select_monday)
    self.monday_canvas.grid(row = 6, padx = 5, sticky = 'W')

    # self.tuesday_canvas = tk.Canvas(self.win, width = 100, height = 20)
    self.tuesday_canvas_rect = self.monday_canvas.create_rectangle(0, 19, 99, 40)
    self.monday_canvas.create_text((5, 30), text = "Tuesday", fill = "#111111", anchor = 'w')
    # self.tuesday_canvas_rect.bind("<Button-1>", self.select_tuesday)
    # self.tuesday_canvas.grid(row = 6, padx = 5, sticky = 'W')

    # self.wednesday_canvas = tk.Canvas(self.win, width = 100, height = 20)
    # self.wednesday_canvas_rect = self.wednesday_canvas.create_rectangle(0, 40, 99, 19, fill = "#E2E2E2", outline = "#000000")
    # self.wednesday_canvas.create_text((5, 10), text = "Wednesday", fill = "#111111", anchor = 'w')
    # self.wednesday_canvas.bind("<Button-1>", self.select_wednesday)
    # # self.wednesday_canvas.grid(row = 8, padx = 5, sticky = 'W')

    # # self.thursday_canvas = tk.Canvas(self.win, width = 100, height = 20)
    # self.thursday_canvas_rect = self.thursday_canvas.create_rectangle(0, 60, 99, 19, fill = "#E2E2E2", outline = "#000000")
    # self.thursday_canvas.create_text((5, 10), text = "Thursday", fill = "#111111", anchor = 'w')
    # self.thursday_canvas.bind("<Button-1>", self.select_thursday)
    # # self.thursday_canvas.grid(row = 9, padx = 5, sticky = 'W')

    # # self.friday_canvas = tk.Canvas(self.win, width = 100, height = 20)
    # self.friday_canvas_rect = self.friday_canvas.create_rectangle(0, 80, 99, 19, fill = "#E2E2E2", outline = "#000000")
    # self.friday_canvas.create_text((5, 10), text = "Friday", fill = "#111111", anchor = 'w')
    # self.friday_canvas.bind("<Button-1>", self.select_friday)
    # # self.friday_canvas.grid(row = 10, padx = 5, sticky = 'W')

    # # self.saturday_canvas = tk.Canvas(self.win, width = 100, height = 20)
    # self.saturday_canvas_rect = self.saturday_canvas.create_rectangle(0, 100, 99, 19, fill = "#E2E2E2", outline = "#000000")
    # self.saturday_canvas.create_text((5, 10), text = "Saturday", fill = "#111111", anchor = 'w')
    # self.saturday_canvas.bind("<Button-1>", self.select_saturday)
    # # self.saturday_canvas.grid(row = 11, padx = 5, sticky = 'W')

    # # self.sunday_canvas = tk.Canvas(self.win, width = 100, height = 20)
    # self.sunday_canvas_rect = self.sunday_canvas.create_rectangle(0, 120, 99, 19, fill = "#E2E2E2", outline = "#000000")
    # self.sunday_canvas.create_text((5, 10), text = "Sunday", fill = "#111111", anchor = 'w')
    # self.sunday_canvas.bind("<Button-1>", self.select_sunday)
    # self.sunday_canvas.grid(row = 12, padx = 5, sticky = 'W')


root = tk.Tk()

app = Application(root)

root.mainloop()