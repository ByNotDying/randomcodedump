import tkinter as tk
from tkinter import scrolledtext
import requests
import json
from pprint import *
win = tk.Tk()


def enter(event):
    win.attributes('-alpha', 1.0)
def leave(event):
    win.attributes('-alpha', 0.4)
    
sText1 = scrolledtext.ScrolledText(win, 
                                      wrap = tk.WORD, 
                                      width = 50, 
                                      height = 10,
                                      # textvariable = "test asdfasdf",
                                      state = 'disabled',
                                      )
sText1.bind("<1>", lambda event: sText1.focus_set())
sText1.grid(row = 1, column = 0, pady = 10, padx = 10)
sText1.configure(state = 'normal')
sText1.insert("end","hello")
sText1.configure(state = 'disabled')


sText2 = scrolledtext.ScrolledText(win, 
                                      wrap = tk.WORD, 
                                      width = 50, 
                                      height = 10,
                                      # textvariable = "test asdfasdf",
                                      # state = 'disabled',
                                      )
sText2.grid(row = 1, column = 1, pady = 10, padx = 10)
sText2.insert("end","hello")


# #make window transparent.
# win.attributes('-alpha', 0.4)

# #when mousing over window, it should be opaque. When mousing out of window, it should be transparent.
# win.bind('<Enter>', enter)
# win.bind('<Leave>', leave)

#the window should always be on top.
win.call('wm', 'attributes', '.', '-topmost', '1')

win.mainloop()