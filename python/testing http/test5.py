import requests
import json
from pprint import *

wf = "https://api.warframe.market/v1"

headers = {
        "platform": "PC",
        "language": "EN",
    }

class Order:
    def __init__(self, rank = 0, quantity = 1, **kwargs):
        # self.IGN = kwargs.get('IGN') #In Game Name
        # self.onlineStatus = kwargs.get('onlineStatus')
        # self.rep = kwargs.get('rep')
        # self.platinum = kwargs.get('platinum') #ALL PRICES ARE IN PLATINUM PER QUANTITY
        # self.quantity = kwargs.get('quantity')
        # self.rank = kwargs.get('rank')
        # self.order_type = kwargs.get('order_type')
        for key, value in kwargs.items():
            setattr(self, key, value)
    def __str__(self):
        return str(self.platinum)
    def __repr__(self):
        return str(self.platinum)


x = requests.get(url = wf + "/items/" + str(input("Enter item name: ")).lower().replace(' ', '_') + "/orders", headers =  headers)
# pprint (x.status_code)
# pprint (x.json())
# pprint (json.loads(x.json()))
# pprint ( json.load(x.json())['payload']['orders']['platinum'] )
# pprint(x.json()['payload']['orders'])

buyList = list() #buy order price list
sellList = list() # sell order price list
buyOrderList = list() #list of items of class Order, containing whatever information you wish to keep track
sellOrderList = list() #list of items of class Order, containing whatever information you wish to keep track
orderList = list() #list of items of class Order, containing whatever information you wish to keep track
allList = list()

for elem in x.json()['payload']['orders']:
    #tempDict = elem(dictionary)
    if elem['user']['status'] != 'offline':
        # print("Online? :", elem['user']['status'], 
             # "| Plat: ", elem['platinum'], 
             # # " | Creation Date: " , elem['creation_date'] 
             # "| Buy/Sell: " , elem['order_type'] , 
              # )
        
        #create buyList and buyOrderList
        if elem['order_type'] == 'buy':
            buyList.append(elem['platinum'])
            buyOrderList.append(Order(**{
            'IGN':elem['user']['ingame_name'] , 
            'onlineStatus':elem['user']['status'] ,
            'rep':elem['user']['reputation'] , 
            'platinum':elem['platinum'] , 
            'quantity':elem['quantity'] ,
            'rank':elem['mod_rank'] , 
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
            'rank':elem['mod_rank'] , 
            'order_type':elem['order_type']
            }))
        
        
        # #create orderList
        # orderList.append(Order(**{
            # 'IGN':elem['user']['ingame_name'] , 
            # 'onlineStatus':elem['user']['status'] ,
            # 'rep':elem['user']['reputation'] , 
            # 'platinum':elem['platinum'] , 
            # 'quantity':elem['quantity'] ,
            # 'rank':elem['mod_rank'] , 
            # 'order_type':elem['order_type']
        # }))

    
print (buyList)
print (sellList)
print (buyOrderList)
print (sellOrderList)

#kwargs example
#c1 = BritCoins(**{"pound":4 , "shilling":24, "penny":3})


#Order Listings are as follows:
#IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
#elem['user']['ingame_name']