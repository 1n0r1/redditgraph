import requests
import json

def get_token():
    clientinfo = open('client_id.txt','r').read().splitlines()

    userinfo =  open('user_info.txt','r').read().splitlines()

    clientid = clientinfo[0]
    clientsecret = clientinfo[1]
    clientredirect = clientinfo[2]

    tokenurl = 'https://www.reddit.com/api/v1/access_token'

    user_name = userinfo[0]
    user_password = userinfo[1]
    data = {
            'grant_type' : 'password',
            'username': user_name,
            'password' : user_password,
            'duration' : 'permanent'
        }


    auth = requests.auth.HTTPBasicAuth(clientid, clientsecret)
    headers = {'User-Agent': 'Graphing/0.0.1'}

    r =requests.post(tokenurl, data=data, auth=auth, headers=headers)
    print(r)
    print(r.json())
    with open('token.json', 'w') as file:
        json.dump(r.json(), file, indent = 4)