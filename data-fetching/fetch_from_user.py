import requests
import json

from requests.models import HTTPError


def fetch_from_user(usern):
    #Read token
    f = open('token.json','r')
    token = json.load(f)
    access_token = token["access_token"]

    #Input: user name
    #Output: a list of 100 newest post id in that subreddit
    def postlist(username): 
        #Get some newest post on a subreddit (r/uiuc)
        postlist = []
        startname = 'null'
        for i in range(1):
            try: #Check if deleted user
                subredditurl = 'https://oauth.reddit.com/user/' + username
                subresponse = requests.get(subredditurl, headers = {
                    'User-Agent': 'Graphing/0.0.1',
                    'Authorization': f'Bearer {access_token}'
                    },
                    params={
                        'after' : startname,
                        'limit' :'1000'
                    })
            except requests.exceptions.HTTPError as e:
                return []
            subredditjson = subresponse.json()
            subresponse.close()
            #Turn into post id
            if not ("data" in subredditjson):
                return[]
            if not ("children" in subredditjson["data"]):
                return[]
            li = subredditjson["data"]["children"]
            for i in li:
                s = i["data"]["subreddit"]
                postlist.append(s)

            startname = subredditjson["data"]["after"]
            if not startname:
                break
        return postlist

    #Input: a list
    #Return: the list without duplicates
    def removeDups(li):
        existed = dict()
        newlist = []
        for i in li:
            if not (i in existed):
                newlist.append(i)
                existed[i] = True
        return newlist

    pl = postlist(usern)
    bef = len(pl)
    pl = removeDups(pl)
    return pl
