#pragma once
#include <fstream>
#include <set>

using namespace std;
//class that reads in subreddit and user files

//how the data directories are expected to be formatted
const string SUBREDDIT_DATA_PATH = "subreddit_text/";
const string USER_DATA_PATH = "user_text/";
const string JSON_SUFFIX = ".json";
const string TXT_SUFFIX = ".txt";

class FileReader {
    public:
        FileReader();
        FileReader(string file_path);

        // Search the file in source/subreddit_text and return the list
        // Return empty set if not found
        set<string> getUserListFromSubRedditFile(string subreddit_name) const;
        
        // Search the file in source/user_text and return the list
        // Return empty set if not found
        set<string> getSubRedditListFromUserFile(string user_name) const;

    private:
        // Contain the directory to the data source so we can easily change which tests, sources we use
        // Example: data-fetching/data, test/test1, test/test2
        string source;
};