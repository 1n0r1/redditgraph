#include "FileReader.h"

FileReader::FileReader() {}

FileReader::FileReader(string file_path) {
    source = file_path;
}

// Search the file in source/subreddit_text and return the list
// Return empty vector if not found
set<string> FileReader::getUserListFromSubRedditFile(string subreddit) const {
    set<string> users;
    
    string user;
    //std::cout << "File: " << source + SUBREDDIT_DATA_PATH + subreddit + TXT_SUFFIX << std::endl;
    ifstream sub_file(source + SUBREDDIT_DATA_PATH + subreddit + TXT_SUFFIX); //gets the relative path to the subreddit filename
    if(sub_file.is_open()) {
        //std::cout << "File Open" << std::endl;
        while(getline(sub_file, user)) {
            if(user != "0" && user != "") {
                users.insert(user);
            }
        }
    }
    return users;
}
        
// Search the file in source/user_text and return the list
// Return empty vector if not found
set<string> FileReader::getSubRedditListFromUserFile(string username) const {
    set<string> subs;
    
    string sub;
    ifstream user_file(source + USER_DATA_PATH + username + TXT_SUFFIX); //gets the relative path to the subreddit filename
    if(user_file.is_open()) {
        while(getline(user_file, sub)) {
            if(sub != "0" && sub != "") {
                subs.insert(sub);
            }
        }
    }
    return subs;
}