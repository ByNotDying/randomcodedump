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
def onClick():
    print(qwer.get())

asdf = tk.Button(win, text="1234", command = onClick)
asdf.grid(row=0)

qwer = tk.Entry(win, text = "default")
qwer.grid(row=2)

print(qwer.get())

# #make window transparent.
# win.attributes('-alpha', 0.4)

# #when mousing over window, it should be opaque. When mousing out of window, it should be transparent.
# win.bind('<Enter>', enter)
# win.bind('<Leave>', leave)

#the window should always be on top.
win.call('wm', 'attributes', '.', '-topmost', '1')

win.mainloop()