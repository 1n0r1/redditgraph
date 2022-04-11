import pandas as pd
import os
# this converts the json files to usable txt files

current_dir = "data/subreddit/"
results_dr = "data/subreddit_text_new/"

# iterate through subreddit json directory making sure we get only json files
for file in os.listdir(current_dir):
    if(file.endswith(".json")): # extra check to make sure file has correct format
        # find the exact path to this json file
        json_name = os.path.join(current_dir, file)

        # read the json file into a python dataframe
        json_df = pd.read_json(json_name)

        subreddit_name = file[0:-5] # isolate the name of the subreddit
        json_df.to_csv(results_dr + subreddit_name + ".txt", index = False)


# repeat same process with users
current_dir = "data/user/"
results_dr = "data/user_text_new/"

# iterate through user json directory, making sure we get only json files
for file in os.listdir(current_dir):
    if(file.endswith(".json")): # extra check to make sure file has correct format
        # find the exact path to this json file
        json_name = os.path.join(current_dir, file)

        # read the json file into a python dataframe
        json_df = pd.read_json(json_name)

        subreddit_name = file[0:-5] # isolate the name of the user by removing the ".json" from the file name
        json_df.to_csv(results_dr + subreddit_name + ".txt", index = False)
