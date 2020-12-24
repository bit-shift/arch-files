import requests
import json

token_url = 'https://oauth.fatsecret.com/connect/token'
api_url = 'https://platform.fatsecret.com/rest/server.api'
client_id = 'c4e7ccb6298b450590c71dd5f4716c61'
client_secret = 'b7f13dd0cefc4c4aa010d6407502c42e'

 
auth = (client_id, client_secret)

headers = {'content-type': 'application/json'}

data = {
    'grant_type': 'client_credentials',
    'scope' : 'basic'
}

req_ret = requests.post(token_url, data=data, auth=auth)

json_dict = json.loads(req_ret.text)
access_token = json_dict["access_token"]

print(access_token)

request_data = {
    'header': {
        'authorization' : 'Bearer ' + access_token
    },
    'form': 'method=foods.search&search_expression=toast&format=json'
}

ret = requests.post(api_url, data=request_data)
# print(ret.text)
