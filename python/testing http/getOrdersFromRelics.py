import requests
import json
from pprint import *
import time
import getOrdersFromItem

headers = {
        "platform": "PC",
        "language": "EN",
    }

#class Relic():

def printTest():
    return "hello world!"

def getItemOrdersLite(userStr, orderList = list()):
    # x = requests.get(url = wf + "/items/" + str(input("Enter item name: ")).lower().replace(' ', '_') + "/orders", headers =  headers)
    wf = "https://api.warframe.market/v1"

    x = requests.get(url = wf + "/items/" + str(userStr).lower().replace(' ', '_') + "/orders", headers =  headers)

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

    return orderList
    
def getRelicItems(userTier, userRelic, itemList = list() ):

    #https://github.com/WFCD/warframe-drop-data#api-endpoints
    wd = "https://drops.warframestat.us/"
    
    #userRefinement = str(input("Enter relic Refinement Level (Intact, Exceptional, Flawless, Radiant)"))
    
    y = requests.get(url = wd + "/data/relics/" + userTier + '/' + userRelic + ".json")
    
    for elem in y.json()['rewards']['Intact']:
        itemList.append(elem['itemName'].replace("Chassis Blueprint","Chassis").replace("Neuroptics Blueprint","Neuroptics").replace("Systems Blueprint","Systems"))
    
    return itemList

    
def main():
    userTier = str(input("Enter relic tier (Lith, Meso, Neo, Axi): "))
    userRelic = str(input("Enter relic name (Letter then number): ")).upper()
    getRelicItems(userTier,userRelic)

if __name__ == "__main__":
    main()

#kwargs example
#c1 = BritCoins(**{"pound":4 , "shilling":24, "penny":3})


#Order Listings are as follows:
#IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
#elem['user']['ingame_name']