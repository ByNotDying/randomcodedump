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


wf = "https://api.warframe.market/v1"

headers = {
        "platform": "PC",
        "language": "EN",
    }

class Order:

    #initialized values should include...
    #IGN, onlineStatus, rep, platinum, quantity, order_type
    #might initialize mod_rank
    
    #Order Listings on warframe.market are as follows:
    #IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
    #I've opted to leave out mod_rank for now.
    
    def __init__(self, rank = 0, quantity = 1, **kwargs):
        for key, value in kwargs.items():
            setattr(self, key, value)

    def __str__(self):
        return str(
             "IGN : " + str(self.IGN) +
             " | onlineStatus : " + str(self.onlineStatus) +
             " | rep : " + str(self.rep) +
             " | platinum : " + str(self.platinum) +
             " | order_type : " + str(self.order_type)
             )

    def __repr__(self):
        return str(
             "IGN : " + str(self.IGN) +
             " | onlineStatus : " + str(self.onlineStatus) +
             " | rep : " + str(self.rep) +
             " | platinum : " + str(self.platinum) +
             " | order_type : " + str(self.order_type) +
             '\n')

#literally just using this for repr
class OrderList():
    def __init__(self, *args):
        self.oList = list()
        for x in args:
            oList.append = args


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

text_area = scrolledtext.ScrolledText(win, 
                                      wrap = tk.WORD, 
                                      width = 100, 
                                      height = 10,
                                      # textvariable = "test asdfasdf",
                                      # state = 'disabled',
                                      )
text_area.grid(column = 0, pady = 10, padx = 10)
text_area.insert("end",repr(getOrders("gale kick")))

sText = scrolledtext.ScrolledText(win, 
                                      wrap = tk.WORD, 
                                      width = 100, 
                                      height = 10,
                                      # textvariable = "test asdfasdf",
                                      # state = 'disabled',
                                      )
sText.grid(column = 0, pady = 10, padx = 10)
sText.insert("end",repr(getOrders("gale kick")))




#make window transparent.
win.attributes('-alpha', 0.4)

#when mousing over window, it should be opaque. When mousing out of window, it should be transparent.
win.bind('<Enter>', enter)
win.bind('<Leave>', leave)

#the window should always be on top.
win.call('wm', 'attributes', '.', '-topmost', '1')

win.mainloop()