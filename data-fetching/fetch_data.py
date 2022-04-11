from get_token import get_token
from fetch_from_subreddit import fetch_from_subreddit
from fetch_from_user import fetch_from_user
import os.path
import json

import threading
import time
def removeDups(li):
    existed = dict()
    newlist = []
    for i in li:
        if not (i in existed):
            newlist.append(i)
            existed[i] = True
    return newlist
def fetch_data(root, depth):
    root_sub = root
    if depth == 0:
        return 0
    userlist = []
    print ("Retriving userlist for " + root_sub)
    if (os.path.exists('data/subreddit/' + root_sub + '.json')):
        userlist = json.load(open('data/subreddit/' + root_sub + '.json','r'))
    else:
        userlist= fetch_from_subreddit(root_sub)
        with open('data/subreddit/' + root_sub + '.json', 'w') as file:
            json.dump(userlist, file, indent = 4)

    k = 0
    subredditList=[]
    for u in userlist:
        k = k+1
        print(k, '/', len(userlist))
        sl = []
        if (os.path.exists('data/user/' + u + '.json')):
            sl = json.load(open('data/user/' + u + '.json', 'r'))
        else:
            sl = fetch_from_user(u)
            with open('data/user/' + u + '.json', 'w') as file:
                json.dump(sl, file, indent = 4)
        for sss in sl:
            subredditList.append(sss)
    k = 0
    subredditList = removeDups(subredditList)
    for sss in subredditList:
        print(sss)
        k = k+1
        print(k, '/', len(subredditList))
        fetch_data(sss, depth - 1)

def renew_token(delay):
    while True:
        get_token()
        time.sleep(delay)

t1 = threading.Thread(target = renew_token, args = (3000, ))
t2 = threading.Thread(target = fetch_data, args = ('UIUC', 2, ))

t1.start()
time.sleep(5)
t2.start()


