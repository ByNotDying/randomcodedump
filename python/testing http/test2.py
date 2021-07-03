import requests
import json
from pprint import *

wf = "https://api.warframe.market/v1"

headers = {
        "platform": "PC",
        "language": "EN",
    }

class Order:

    #initialized values should include...
    #IGN, onlineStatus, rep, platinum, quantity, order_type
    #might initialize mod_rank
    
    #If you will notice below, there is a block of code in the main function
    #therefore, you (me in the future) might want to change this into a function that takes a json, and then creates class variables based on what exists in the json.
    #that might be more memory intesnive, unless we were to only check the json for a few set variables... but that might take us back to the reason 
    def __init__(self, rank = 0, quantity = 1, **kwargs):
        for key, value in kwargs.items():
            setattr(self, key, value)
            
    #Order Listings on warframe.market are as follows:
        #IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
        #I've opted to leave out mod_rank for now.
    # def __str__(self):
        # return str(self.platinum)
    # def __repr__(self):
        # return str(self.platinum)
        
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



def main():

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
        
        #TODO: This entire block of code is a monstrosity. Might want to change it.
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

        
    # print (buyList)
    # print (sellList)
    # print (buyOrderList)
    # print (sellOrderList)

    for elem in buyOrderList:
        print(elem)

    for elem in sellOrderList:
        print(elem)
    
    
if __name__ == "__main__":
    main()

#kwargs example
#c1 = BritCoins(**{"pound":4 , "shilling":24, "penny":3})


#Order Listings are as follows:
#IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
#elem['user']['ingame_name']