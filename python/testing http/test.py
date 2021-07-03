import json
import http.client


py = http.client.HTTPConnection('www.python.org')

wf = http.client.HTTPConnection('api.warframe.market/v1', 80)



wf.request("GET","api.warframe.market/items")


# conn=http.client.HTTPSConnection('www.python.com')
# conn.request("GET", "/")
# res=conn.getresponse()
# print(conn)



# connection = http.client.HTTPSConnection("www.journaldev.com")
# connection.request("GET", "/")
# response = connection.getresponse()
# headers = response.getheaders()
# pp = pprint.PrettyPrinter(indent=4)
# pp.pprint("Headers: {}".format(headers))