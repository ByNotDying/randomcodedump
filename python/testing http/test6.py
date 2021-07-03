import requests
import json
from pprint import *

#https://drops.warframestat.us/data/relics.json
#https://drops.warframestat.us/data/relics/$TIER/$RELIC_NAME.json

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
    
    wf = "https://api.warframe.market/v1"

    wfheaders = {
        "platform": "PC",
        "language": "EN",
    }

    x = requests.get(url = str(input("enter api get url")), headers = wfheaders)
    pprint(x.json())
   

    


    

   
    
    
if __name__ == "__main__":
    main()

#kwargs example
#c1 = BritCoins(**{"pound":4 , "shilling":24, "penny":3})


#Order Listings are as follows:
#IGN , ONLINE STATUS, REPUTATION, UNIT PRICE, QUANTITY, RANK, BUY/SELL ORDERS  
#elem['user']['ingame_name']