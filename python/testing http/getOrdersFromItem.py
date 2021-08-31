import requests
import json
import time
from pprint import *

wf = "https://api.warframe.market/v1"

headers = {
        "platform": "PC",
        "language": "EN",
    }

class Order: #This is just a dictionary. It is useful for keeping everything organized and easily printable, though.

    #initialized values should include...
    #IGN, onlineStatus, rep, platinum, quantity, order_type
    #might initialize mod_rank
    
    #you (me in the future) might want to change this into a function that takes a json, and then creates class variables based on what exists in the json.
    #that might be more memory intesnive, unless we were to only check the json for a few set variables... but that might take us back to the reason 
    def __init__(self, rank = 0, quantity = 1, **kwargs):
        
        #I've initialized these in order to more simply deal with these later.
        self.rank = rank
        self.quantity = quantity
        for key, value in kwargs.items():
            setattr(self, key, value)
            
    #Order Listings on warframe.market are as follows:
        #IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
        #I've opted to leave out mod_rank for now.
        
    def __str__(self):
        return str(
             "IGN : " + str(self.IGN) +
             " | " + str(self.onlineStatus) +
             " | " + str(self.rep) + "☺"
             " | " + str(self.platinum) + "p" + 
             " | " + str(self.order_type) +
             " | " + str(self.quantity) + "x"
             )
    def __repr__(self):
        return str(
             "IGN : " + str(self.IGN) +
             " | " + str(self.onlineStatus) +
             " | " + str(self.rep) + "☺"
             " | " + str(self.platinum) + "p" + 
             " | " + str(self.order_type) +
             " | " + str(self.quantity) + "x"
             '\n')
    def altrepr(self):
        return str(
             str(self.order_type).capitalize() + " | "
             + str(self.platinum) + "p" + 
             " | IGN : " + str(self.IGN) +
             " | " + str(self.onlineStatus) +
             " | " + str(self.rep) + "☺"
             " | " + str(self.quantity) + "x"
             '\n')



def getItemOrders(itemName, orderList = list(), orderType = 'all'): #orderType should 
    
    
    buyList = list()
    sellList = list()
    orderType = str(orderType).lower()
    
    #deal with formas
    if itemName == "Forma" or itemName == "Forma Blueprint":
        orderList.append(Order(**{
                    'IGN':'FORMA' , 
                    'onlineStatus':'online' ,
                    'rep':'0' , 
                    'platinum':'12' , 
                    'quantity':'1' ,
                    # 'rank':elem['mod_rank'] , 
                    'order_type':'sell'
                    }))
        return orderList

    x = requests.get(url = wf + "/items/" + str(itemName).lower().replace(' ', '_') + "/orders", headers =  headers)
    
    #this should be changed to handle different types of orders or information- such as auctions or item data from warframe.market
    if orderType != 'buy' and orderType != 'sell':
        for elem in x.json()['payload']['orders']:
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
                
    
    #the purpose of this loop is to filter out buy and/or sell orders.
    elif orderType == 'buy' or orderType == 'sell':
        for elem in x.json()['payload']['orders']:        
            if elem['user']['status'] != 'offline':#if user has not set state to offline/invisible
                if elem['order_type'] == orderType:
                    orderList.append(Order(**{
                    'IGN':elem['user']['ingame_name'] , 
                    'onlineStatus':elem['user']['status'] ,
                    'rep':elem['user']['reputation'] , 
                    'platinum':elem['platinum'] , 
                    'quantity':elem['quantity'] ,
                    # 'rank':elem['mod_rank'] , 
                    'order_type':elem['order_type']
                    }))
                

    #This sorts the orderList by plat amount.
    # orderList = sorted(orderList, key = lambda elem: elem.platinum)
    orderList.sort(key = lambda elem: (elem.order_type, -elem.platinum))



    return orderList
    
def main():
    getItemOrders()

if __name__ == "__main__":
    main()

#kwargs example
#c1 = BritCoins(**{"pound":4 , "shilling":24, "penny":3})


#Order Listings are as follows:
#IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
#elem['user']['ingame_name']