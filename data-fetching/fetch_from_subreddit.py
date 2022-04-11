import requests
import json

def fetch_from_subreddit(subr):

    #Read token
    f = open('token.json','r')
    token = json.load(f)
    access_token = token["access_token"]

    #Input: subreddit name
    #Output: a list of comments in that subreddit
    def postlist(subred): 
        #Get some newest comments on a subreddit
        postlist = []
        startname = 'null'
        for i in range(15):
            subredditurl = 'https://oauth.reddit.com/r/' + subred +'/comments'
            subresponse = requests.get(subredditurl, headers = {
                'User-Agent': 'Graphing/0.0.1',
                'Authorization': f'Bearer {access_token}'
                },
                params={
                    'after' : startname,
                    'limit' :'1000'
                })
            subredditjson = subresponse.json()
            subresponse.close()
            try:
                li = subredditjson["data"]["children"]
                for i in li:
                    postlist.append(i["data"]["link_author"])
                    postlist.append(i["data"]["author"])
            except:
                True
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

    alluserslist = []
    alluserslist = postlist(subr)

    alluserslist = removeDups(alluserslist)

    return alluserslist
