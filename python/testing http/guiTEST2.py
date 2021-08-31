import tkinter as tk
from tkinter import ttk
import requests
import json
from pprint import *
import collections
import threading
import getOrdersFromRelics as gofr
import getOrdersFromItem as gofi

win = tk.Tk()

# def enter(event):
    # win.attributes('-alpha', 1.0)
# def leave(event):
    # win.attributes('-alpha', 0.4)

def makeGriandgorThread(event=None):
    threading.Thread(target = griandgor).start()

def griandgor(event=None):
    
    #stuff for color
    setTextBoxColors()
    
    for entry,textList in myEntryTextDict.items():
    
        tempItemList = list()
        gofr.getRelicItems(tierCBox.get().capitalize(),entry.get().upper(),tempItemList)
        
        for textBox in textList:
            itemName = tempItemList.pop()
            tempOrders = list()
            gofi.getItemOrders(itemName,tempOrders)

            myTextLabelDict[textBox]['text'] = itemName
            
            textBox.configure(state = 'normal')
            
            for elem in tempOrders:
                if elem.order_type == "buy":
                    textBox.insert("end", elem.altrepr(), 'buy')
                elif elem.order_type == "sell":
                    textBox.insert("end", elem.altrepr(), 'sell')
                else:
                    textBox.insert("end", elem.altrepr(), 'sell')


def setTextBoxColors():
    for elem in myTextBoxList:
            elem.tag_config('sell', foreground='red')
            elem.tag_config('buy', foreground='green')
            elem.delete('1.0', tk.END)

wf = "https://api.warframe.market/v1"

headers = {
        "platform": "PC",
        "language": "EN",
    }

    

# greeting = tk.Label(text=repr(getOrders("gale kick")))
# greeting.pack()

#1

#list of all entry boxes
myEntryBoxList = list()
#list of the order of items in which I should have the insertion cursor jump to, as well as events to activate in the event I reached the last one
myTextBoxList= list()
myEntryTextDict = dict()
myTextLabelList = list()
myTextLabelDict = dict()

myFrame = tk.Frame(win)
myFrame.grid(row = 00, column = 00, sticky = 'ew', columnspan = 900)

# myFrame.bind('<Enter>', enter)
# myFrame.bind('<Leave>', leave)

for x in range(4):

    myEntryLabel= tk.Label(myFrame, text = "Relic Name")
    myEntryLabel.pack   (side = 'left')
    
    myEntry = tk.Entry(myFrame, width = 3)
    myEntry.pack(side = 'left')
    myEntryBoxList.append(myEntry)
    myEntry.bind('<Return>', lambda event: event.widget.tk_focusNext().focus())
    
    for y in range(6):
    
        myLabel = tk.Label(win,text = "test")
        myLabel.grid(row = y*10+9,column = x*10)
        myTextLabelList.append(myLabel)
        
        myText = tk.Text(win, 
                          wrap = "none", 
                          width = 50, 
                          height = 6,
                          # textvariable = "test asdfasdf",
                          state = 'disabled',
                          )
        myText.bind("<1>", lambda event: myText.focus_set())
        myText.grid(row = y*10+10, column = x*10) #row/column determine where things get put. padx, pady is vertical and horziontal space padding, to make sure the box doesn't end at the end of the window.
        myText.configure(state = 'normal')
        # sText1.insert("end",repr(gofi.getItemOrders("gale kick")))
        myText.configure(state = 'disabled')
        myTextBoxList.append(myText)
        myEntryTextDict.setdefault(myEntry,[]).append(myText)
        
        myTextLabelDict[myText] = myLabel

        #hori scroll
        myTextHScroll = tk.Scrollbar(win, orient="horizontal", command=myText.xview)
        myTextHScroll.grid(row = y*10+11, column = x*10, sticky = "ew")
        #verti scroll
        myTextVScroll = tk.Scrollbar(win, orient="vertical", command=myText.yview)
        myTextVScroll.grid(row = y*10+10, column = x*10+9, sticky = "ns")

tierCBox = ttk.Combobox(myFrame, values = ["Lith","Meso","Neo","Axi"])
tierCBox.pack(side = 'right')
# tierCBox.bind("<Return>", griandgor)
tierCBox.bind("<Return>", makeGriandgorThread)


# threading.Thread(target = tierCBox.bind, args = ["<Return>", griandgor]).start()

tierLabel = tk.Label(myFrame, text = "Relic Tier")
tierLabel.pack(side = 'right')

# #make window transparent.
# win.attributes('-alpha', 0.4)

# #when mousing over window, it should be opaque. When mousing out of window, it should be transparent.
# win.bind('<Enter>', enter)
# win.bind('<Leave>', leave)

# #makes window always be on top.
# win.call('wm', 'attributes', '.', '-topmost', '1')

myEntryBoxList[0].focus()

win.mainloop()