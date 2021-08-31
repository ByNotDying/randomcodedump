import tkinter as tk
from tkinter import ttk
import requests
import json
from pprint import *
import getOrdersFromRelics as gofr
import getOrdersFromItem as gofi
import collections
import threading
win = tk.Tk()



def enter(event):
    win.attributes('-alpha', 1.0)
def leave(event):
    win.attributes('-alpha', 0.4)

def griandgor(entry):

    #stuff for color
    sText1.tag_config('sell', foreground='red')
    sText1.tag_config('buy', foreground='green')
    
    #column 1 Item list
    # print(f4C1.get().capitalize()+' '+f1E2.get().upper())
    c1ItemList = gofr.getRelicItems(f4C1.get().capitalize(),f1E2.get().upper())
    c1Orders1 = gofi.getItemOrders(c1ItemList[0])
    sText1.configure(state = 'normal')
    for elem in c1Orders1:
        if elem.order_type == "buy":
            sText1.insert("end", elem.altrepr(), 'buy')
        if elem.order_type == "sell":
            sText1.insert("end", elem.altrepr(), 'sell')
    sText1.configure(state = 'disabled')
    #c1Orders2
    #c1Orders3
    #c1Orders4
    #c1Orders5
    #c1Orders6
    print(f4C1.get().capitalize()+' '+f2E2.get().upper())
    print(f4C1.get().capitalize()+' '+f3E2.get().upper())
    print(f4C1.get().capitalize()+' '+f4E2.get().upper())
    


wf = "https://api.warframe.market/v1"

headers = {
        "platform": "PC",
        "language": "EN",
    }

def getOrders(userStr):

    # x = requests.get(url = wf + "/items/" + str(input("Enter item name: ")).lower().replace(' ', '_') + "/orders", headers =  headers)
    
    x = requests.get(url = wf + "/items/" + str(userStr).lower().replace(' ', '_') + "/orders", headers =  headers)

    buyList = list() #buy order price list
    sellList = list() # sell order price list
    orderList = list() #list of items of class Order, containing whatever information you wish to keep track
    allList = list()

    for elem in x.json()['payload']['orders']:
        #if the creator of the order is currently online, store the order info as a dictionary into the appropriate list
        if elem['user']['status'] != 'offline':
            
            #create orderList
            orderList.append(Order(**{
                'IGN':elem['user']['ingame_name'] , 
                'onlineStatus':elem['user']['status'] ,
                'rep':elem['user']['reputation'] , 
                'platinum':elem['platinum'] , 
                'quantity':elem['quantity'] ,
                # 'rank':elem['mod_rank'] , 
                'order_type':elem['order_type']
            }))

    # print (buyList)
    # print (sellList)
    # print (buyOrderList)
    # print (sellOrderList)

    return orderList
    

# greeting = tk.Label(text=repr(getOrders("gale kick")))
# greeting.pack()

#1
f1 = tk.Frame(win)
f1.grid(row = 00, column = 00, sticky = 'ew', columnspan = 2)

f1L2= tk.Label(f1, text = "Relic Name")
f1L2.pack(side = 'left')
f1E2 = tk.Entry(f1, width = 3)
f1E2.pack(side = 'left')
f1E2.bind('<Return>', lambda x:f2E2.focus_set())



l1 = tk.Label(win,text = "test")
l1.grid(row = 9,column = 00)

sText1 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText1.bind("<1>", lambda event: sText1.focus_set())
sText1.grid(row = 10, column = 00) #row/column determine where things get put. padx, pady is vertical and horziontal space padding, to make sure the box doesn't end at the end of the window.
sText1.configure(state = 'normal')
# sText1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText1.configure(state = 'disabled')

#hori scroll
sText1Hsb = tk.Scrollbar(win, orient="horizontal", command=sText1.xview)
sText1Hsb.grid(row = 20, column = 00, sticky = "ew")
#verti scroll
sText1Vsb = tk.Scrollbar(win, orient="vertical", command=sText1.yview)
sText1Vsb.grid(row = 10, column = 10, sticky = "ns")

l1_1 = tk.Label(win,text = "test")
l1_1.grid(row = 29,column = 00)

sText1_1 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText1_1.bind("<1>", lambda event: sText1.focus_set())

sText1_1.grid(row = 30, column = 00, sticky = 'news') 
sText1_1.configure(state = 'normal')
# sText1_1.insert("end", )
sText1_1.configure(state = 'disabled')

#hori scroll
sText1_1Hsb = tk.Scrollbar(win, orient="horizontal", command=sText1.xview)
sText1_1Hsb.grid(row = 40, column = 00, sticky = "ew")
#verti scroll
sText1_1Vsb = tk.Scrollbar(win, orient="vertical", command=sText1.yview)
sText1_1Vsb.grid(row = 30, column = 10, sticky = "ns")

l1_2 = tk.Label(win,text = "test")
l1_2.grid(row = 49,column = 00, sticky = 'news')

sText1_2 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText1_2.bind("<1>", lambda event: sText1.focus_set())

sText1_2.grid(row = 50, column = 00, sticky = 'news') 
sText1_2.configure(state = 'normal')
# sText1_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText1_2.configure(state = 'disabled')

#hori scroll
sText1_2Hsb = tk.Scrollbar(win, orient="horizontal", command=sText1.xview)
sText1_2Hsb.grid(row = 60, column = 00, sticky = "ew")
#verti scroll
sText1_2Vsb = tk.Scrollbar(win, orient="vertical", command=sText1.yview)
sText1_2Vsb.grid(row = 50, column = 10, sticky = "ns")

l1_3 = tk.Label(win,text = "test")
l1_3.grid(row = 69,column = 00, sticky = 'news')

sText1_3 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText1_3.bind("<1>", lambda event: sText1.focus_set())

sText1_3.grid(row = 70, column = 00) 
sText1_3.configure(state = 'normal')
# sText1_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText1_3.configure(state = 'disabled')

#hori scroll
sText1_3Hsb = tk.Scrollbar(win, orient="horizontal", command=sText1.xview)
sText1_3Hsb.grid(row = 80, column = 00, sticky = "ew")
#verti scroll
sText1_3Vsb = tk.Scrollbar(win, orient="vertical", command=sText1.yview)
sText1_3Vsb.grid(row = 70, column = 10, sticky = "ns")


#2
f2 = tk.Frame(win)
f2.grid(row = 00, column = 20, sticky = 'ew', columnspan = 2)#columnspan = 2 , sticky = 'ew'

f2L2= tk.Label(f2, text = "Relic Name")
f2L2.pack(side = 'left')
f2E2 = tk.Entry(f2, width = 3)
f2E2.pack(side = 'left')
f2E2.bind('<Return>', lambda x:f3E2.focus_set())

l2 = tk.Label(win,text = "test")
l2.grid(row = 9,column = 20, sticky = 'news')

sText2 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  # state = 'disabled',
                  )
sText2.bind("<1>", lambda event: sText1.focus_set())
sText2.grid(row = 10, column = 20) #row/column determine where things get put. padx, pady is vertical and horziontal space padding, to make sure the box doesn't end at the end of the window.
sText2.configure(state = 'normal')
# sText2.insert("end",repr(gofi.getItemOrders("gale kick")))
sText2.configure(state = 'disabled')

#hori scroll
sText2Hsb = tk.Scrollbar(win, orient="horizontal", command=sText2.xview)
sText2Hsb.grid(row = 20, column = 20, sticky = "ew")
#verti scroll
sText2Vsb = tk.Scrollbar(win, orient="vertical", command=sText2.yview)
sText2Vsb.grid(row = 10, column = 30, sticky = "ns")

l2_1 = tk.Label(win,text = "test")
l2_1.grid(row = 29,column = 20, sticky = 'news')

sText2_1 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText2_1.bind("<1>", lambda event: sText2.focus_set())

sText2_1.grid(row = 30, column = 20) 
sText2_1.configure(state = 'normal')
# sText2_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText2_1.configure(state = 'disabled')

#hori scroll
sText2_1Hsb = tk.Scrollbar(win, orient="horizontal", command=sText2.xview)
sText2_1Hsb.grid(row = 40, column = 20, sticky = "ew")
#verti scroll
sText2_1Vsb = tk.Scrollbar(win, orient="vertical", command=sText2.yview)
sText2_1Vsb.grid(row = 30, column = 30, sticky = "ns")

l2_2 = tk.Label(win,text = "test")
l2_2.grid(row = 49,column = 20, sticky = 'news')

sText2_2 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText2_2.bind("<1>", lambda event: sText2.focus_set())

sText2_2.grid(row = 50, column = 20) 
sText2_2.configure(state = 'normal')
# sText2_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText2_2.configure(state = 'disabled')

#hori scroll
sText2_2Hsb = tk.Scrollbar(win, orient="horizontal", command=sText2.xview)
sText2_2Hsb.grid(row = 60, column = 20, sticky = "ew")
#verti scroll
sText2_2Vsb = tk.Scrollbar(win, orient="vertical", command=sText2.yview)
sText2_2Vsb.grid(row = 50, column = 30, sticky = "ns")

l2_3 = tk.Label(win,text = "asdfasdf")
l2_3.grid(row = 69,column = 20, sticky = 'news')

sText2_3 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText2_3.bind("<1>", lambda event: sText2.focus_set())

sText2_3.grid(row = 70, column = 20) 
sText2_3.configure(state = 'normal')
# sText2_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText2_3.configure(state = 'disabled')

#hori scroll
sText2_3Hsb = tk.Scrollbar(win, orient="horizontal", command=sText2.xview)
sText2_3Hsb.grid(row = 80, column = 20, sticky = "ew")
#verti scroll
sText2_3Vsb = tk.Scrollbar(win, orient="vertical", command=sText2.yview)
sText2_3Vsb.grid(row = 70, column = 30, sticky = "ns")

#3
f3 = tk.Frame(win)
f3.grid(row = 00, column = 40, sticky = 'ew', columnspan = 2)

f3L2= tk.Label(f3, text = "Relic Name")
f3L2.pack(side = 'left')
f3E2 = tk.Entry(f3, width = 3)
f3E2.pack(side = 'left')
f3E2.bind('<Return>', lambda x:f4E2.focus_set())


l3 = tk.Label(win,text = "asdfasdf")
l3.grid(row = 9,column = 40, sticky = 'news')

sText3 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText3.bind("<1>", lambda event: sText3.focus_set())
sText3.grid(row = 10, column = 40) #row/column determine where things get put. padx, pady is vertical and horziontal space padding, to make sure the box doesn't end at the end of the window.
sText3.configure(state = 'normal')
# sText3.insert("end",repr(gofi.getItemOrders("gale kick")))
sText3.configure(state = 'disabled')

#hori scroll
sText3Hsb = tk.Scrollbar(win, orient="horizontal", command=sText3.xview)
sText3Hsb.grid(row = 20, column = 40, sticky = "ew")
#verti scroll
sText3Vsb = tk.Scrollbar(win, orient="vertical", command=sText3.yview)
sText3Vsb.grid(row = 10, column = 50, sticky = "ns")

l3_1 = tk.Label(win,text = "asdfasdf")
l3_1.grid(row = 29,column = 40, sticky = 'news')

sText3_1 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText3_1.bind("<1>", lambda event: sText3.focus_set())

sText3_1.grid(row = 30, column = 40) 
sText3_1.configure(state = 'normal')
# sText3_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText3_1.configure(state = 'disabled')

#hori scroll
sText3_1Hsb = tk.Scrollbar(win, orient="horizontal", command=sText3.xview)
sText3_1Hsb.grid(row = 40, column = 40, sticky = "ew")
#verti scroll
sText3_1Vsb = tk.Scrollbar(win, orient="vertical", command=sText3.yview)
sText3_1Vsb.grid(row = 30, column = 50, sticky = "ns")

l3_2 = tk.Label(win,text = "asdfasdf")
l3_2.grid(row = 49,column = 40, sticky = 'news')

sText3_2 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText3_2.bind("<1>", lambda event: sText3.focus_set())

sText3_2.grid(row = 50, column = 40) 
sText3_2.configure(state = 'normal')
# sText3_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText3_2.configure(state = 'disabled')

#hori scroll
sText3_2Hsb = tk.Scrollbar(win, orient="horizontal", command=sText3.xview)
sText3_2Hsb.grid(row = 60, column = 40, sticky = "ew")
#verti scroll
sText3_2Vsb = tk.Scrollbar(win, orient="vertical", command=sText3.yview)
sText3_2Vsb.grid(row = 50, column = 50, sticky = "ns")

l3_3 = tk.Label(win,text = "asdfasdf")
l3_3.grid(row = 69,column = 40, sticky = 'news')

sText3_3 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText3_3.bind("<1>", lambda event: sText3.focus_set())

sText3_3.grid(row = 70, column = 40) 
sText3_3.configure(state = 'normal')
# sText3_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText3_3.configure(state = 'disabled')

#hori scroll
sText3_3Hsb = tk.Scrollbar(win, orient="horizontal", command=sText3.xview)
sText3_3Hsb.grid(row = 80, column = 40, sticky = "ew")
#verti scroll
sText3_3Vsb = tk.Scrollbar(win, orient="vertical", command=sText3.yview)
sText3_3Vsb.grid(row = 70, column = 50, sticky = "ns")


#4
f4 = tk.Frame(win)
f4.grid(row = 00, column = 60, sticky = 'ew', columnspan = 2)

f4b1 = tk.Button(f4, text = "Enter")
f4b1.pack(side = "right", padx = (20,0))

f4C1 = ttk.Combobox(f4, values = ["Lith","Meso","Neo","Axi"])
f4C1.pack(side = 'right')
f4C1.bind("<Return>",griandgor)

f4L1 = tk.Label(f4, text = "Relic Tier")
f4L1.pack(side = 'right')

f4L2= tk.Label(f4, text = "Relic Name")
f4L2.pack(side = 'left')
f4E2 = tk.Entry(f4, width = 3)
f4E2.pack(side = 'left')
f4E2.bind('<Return>', lambda x:f4C1.focus_set())



l4 = tk.Label(win,text = "asdfasdf")
l4.grid(row = 9,column = 60, sticky = 'news')

sText4 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText4.grid(row = 10, column = 60) #row/column determine where things get put. padx, pady is vertical and horziontal space padding, to make sure the box doesn't end at the end of the window.
sText4.configure(state = 'normal')
# sText4.insert("end",repr(gofi.getItemOrders("gale kick")))
sText4.configure(state = 'disabled')

#hori scroll
sText4Hsb = tk.Scrollbar(win, orient="horizontal", command=sText4.xview)
sText4Hsb.grid(row = 20, column = 60, sticky = "ew")
#verti scroll
sText4Vsb = tk.Scrollbar(win, orient="vertical", command=sText4.yview)
sText4Vsb.grid(row = 10, column = 70, sticky = "ns")

l4_1 = tk.Label(win,text = "asdfasdf")
l4_1.grid(row = 29,column = 60, sticky = 'news')

sText4_1 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText4_1.bind("<1>", lambda event: sText4.focus_set())

sText4_1.grid(row = 30, column = 60) 
sText4_1.configure(state = 'normal')
# sText4_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText4_1.configure(state = 'disabled')

#hori scroll
sText4_1Hsb = tk.Scrollbar(win, orient="horizontal", command=sText4.xview)
sText4_1Hsb.grid(row = 40, column = 60, sticky = "ew")
#verti scroll
sText4_1Vsb = tk.Scrollbar(win, orient="vertical", command=sText4.yview)
sText4_1Vsb.grid(row = 30, column = 70, sticky = "ns")

l4_2 = tk.Label(win,text = "asdfasdf")
l4_2.grid(row = 49,column = 60, sticky = 'news')

sText4_2 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText4_2.bind("<1>", lambda event: sText4.focus_set())

sText4_2.grid(row = 50, column = 60) 
sText4_2.configure(state = 'normal')
# sText4_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText4_2.configure(state = 'disabled')

#hori scroll
sText4_2Hsb = tk.Scrollbar(win, orient="horizontal", command=sText4.xview)
sText4_2Hsb.grid(row = 60, column = 60, sticky = "ew")
#verti scroll
sText4_2Vsb = tk.Scrollbar(win, orient="vertical", command=sText4.yview)
sText4_2Vsb.grid(row = 50, column = 70, sticky = "ns")

l4_3 = tk.Label(win,text = "asdfasdf")
l4_3.grid(row = 69,column = 60, sticky = 'news')

sText4_3 = tk.Text(win, 
                  wrap = "none", 
                  width = 50, 
                  height = 10,
                  # textvariable = "test asdfasdf",
                  state = 'disabled',
                  )
sText4_3.bind("<1>", lambda event: sText4.focus_set())

sText4_3.grid(row = 70, column = 60) 
sText4_3.configure(state = 'normal')
# sText4_1.insert("end",repr(gofi.getItemOrders("gale kick")))
sText4_3.configure(state = 'disabled')

#hori scroll
sText4_3Hsb = tk.Scrollbar(win, orient="horizontal", command=sText4.xview)
sText4_3Hsb.grid(row = 80, column = 60, sticky = "ew")
#verti scroll
sText4_3Vsb = tk.Scrollbar(win, orient="vertical", command=sText4.yview)
sText4_3Vsb.grid(row = 70, column = 70, sticky = "ns")

#make window transparent.
win.attributes('-alpha', 0.4)

#when mousing over window, it should be opaque. When mousing out of window, it should be transparent.
win.bind('<Enter>', enter)
win.bind('<Leave>', leave)

#the window should always be on top.
win.call('wm', 'attributes', '.', '-topmost', '1')

win.mainloop()