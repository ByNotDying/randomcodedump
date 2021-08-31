import requests
import json
from pprint import *
import time

headers = {
        "platform": "PC",
        "language": "EN",
    }

class Order:

    #initialized values should include...
    #IGN, onlineStatus, rep, platinum, quantity, order_type
    #might initialize mod_rank
    
    def __init__(self, rank = 0, quantity = 1, **kwargs):
        for key, value in kwargs.items():
            setattr(self, key, value)
            
    #Order Listings on warframe.market are as follows:
        #IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
        #I've opted to leave out mod_rank for now.
        
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


#class Relic(): # maybe make this, maybe.

def getItemOrders(itemName):

    wf = "https://api.warframe.market/v1"
    x = requests.get(url = wf + "/items/" + str(itemName).lower().replace(' ', '_').strip('\'') + "/orders", headers =  headers)

    buyList = list() #buy order price list
    sellList = list() # sell order price list
    buyOrderList = list() #list of items of class Order, containing whatever information you wish to keep track
    sellOrderList = list() #list of items of class Order, containing whatever information you wish to keep track
    orderList = list() #list of items of class Order, containing whatever information you wish to keep track
    allList = list()


    for elem in x.json()['payload']['orders']:
        
        #TODO: This entire block of code is a monstrosity. Might want to change it.
        if elem['user']['status'] != 'offline':
            
            if elem['order_type'] == 'buy':
                buyList.append(elem['platinum'])
                buyOrderList.append(Order(**{
                'IGN':elem['user']['ingame_name'] , 
                'onlineStatus':elem['user']['status'] ,
                'rep':elem['user']['reputation'] , 
                'platinum':elem['platinum'] , 
                'quantity':elem['quantity'] ,
                #'rank':elem['mod_rank'] , 
                'order_type':elem['order_type']
                }))
                
            #create sellList and sellOrderList
            elif elem['order_type'] == 'sell':
                sellList.append(elem['platinum'])
                sellOrderList.append(Order(**{
                'IGN':elem['user']['ingame_name'] , 
                'onlineStatus':elem['user']['status'] ,
                'rep':elem['user']['reputation'] , 
                'platinum':elem['platinum'] , 
                'quantity':elem['quantity'] ,
                # 'rank':elem['mod_rank'] , 
                'order_type':elem['order_type']
                }))
            
            
            # #create orderList
            # orderList.append(Order(**{
                # 'IGN':elem['user']['ingame_name'] , 
                # 'onlineStatus':elem['user']['status'] ,
                # 'rep':elem['user']['reputation'] , 
                # 'platinum':elem['platinum'] , 
                # 'quantity':elem['quantity'] ,
                # # 'rank':elem['mod_rank'] , 
                # 'order_type':elem['order_type']
            # }))

    for elem in buyOrderList:
        print(elem)

    for elem in sellOrderList:
        print(elem)
    
def getRelicItems():
    #https://github.com/WFCD/warframe-drop-data#api-endpoints
    
    wd = "https://drops.warframestat.us/"
    
    userTier = str(input("Enter relic tier (Lith, Meso, Neo, Axi): "))
    userRelic = str(input("Enter relic name (Letter then number): ")).upper()
    #userRefinement = str(input("Enter relic Refinement Level (Intact, Exceptional, Flawless, Radiant)"))
    
    y = requests.get(url = wd + "/data/relics/" + userTier + '/' + userRelic + ".json")
    pprint(y.json())
    
    for elem in y.json()['rewards']['Intact']:
        print(elem['itemName'].replace("Chassis Blueprint","Chassis").replace("Neuroptics Blueprint","Neuroptics").replace("Systems Blueprint","Systems"))
        getItemOrders(elem['itemName'].replace("Chassis Blueprint","Chassis").replace("Neuroptics Blueprint","Neuroptics").replace("Systems Blueprint","Systems"))
        time.sleep(1)

    
    #for elem in ItemList:
        #getItemOrders():

    
def main():
    getRelicItems()

if __name__ == "__main__":
    main()

#kwargs example
#c1 = BritCoins(**{"pound":4 , "shilling":24, "penny":3})


#Order Listings are as follows:
#IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
#elem['user']['ingame_name']