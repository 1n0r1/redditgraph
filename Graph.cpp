#include "Graph.h"
#include "PriorityQueue.h"
#include <algorithm>

Graph::Graph() {
    //default
}

Graph::Graph(string source_directory) {
    reader = FileReader(source_directory);
}

Graph::~Graph() {
    clear();
}
int Graph::getMaxConnection() const {
    return max_connection;
}
void Graph::readGraphBFS(string root) {
    queue<string> subReddit;
    subReddit.push(root);
    int pop = 1;
    while(!subReddit.empty()) {
        //populate the subreddit in the front of the qeueu
        string sub = subReddit.front();
        pop++;
        subReddit.pop();
        populateSubreddit(sub);
        SubReddit* subPtr = retrieveSubreddit(sub);
        std::cout << "Populated: " << pop << std::endl;
        //now add the adjacent ones to the queue
        for(map<SubReddit*, int>::iterator it = subPtr->adjacent.begin(); it != subPtr->adjacent.end(); it++) {
            if(read_subs.find(it->first->name) != read_subs.end()) { //already read this subreddit 
                //do nothing
            } else {
                //recursively read this next subreddit
                subReddit.push(it->first->name);
                read_subs.insert(it->first->name);
            }
        }
    }
}

vector<string> Graph::BFSTraversal(string start) const {
    queue<string> subReddit;
    subReddit.push(start);
    vector<string> ret;
    set<string> seen_subs; // A set to store subs that have already been seen
    seen_subs.insert(start);

    while(!subReddit.empty()) {
        string sub = subReddit.front();
        subReddit.pop();
        SubReddit* subPtr = unique_subreddits.find(sub)->second;
        ret.push_back(subPtr->name);
        //add the adjacent subreddits to queue in alphabetical order
        //(original code created different BFS outputs each time, so do this to make more uniform/testable)
        
        //create a vector of adjacent subreddits
        vector<string> adjacent;
        for(map<SubReddit*, int>::iterator it = subPtr->adjacent.begin(); it != subPtr->adjacent.end(); it++) {
            adjacent.push_back(it->first->name);
        }
        //sort the vector
        sort(adjacent.begin(), adjacent.end());

        //now add the adjacent subreddits
        for(string adj : adjacent) {
            if(seen_subs.find(adj) != seen_subs.end()) { //already read this subreddit 
                //do nothing
            } else {
                subReddit.push(adj);
                seen_subs.insert(adj);
            }
        }
    }
    return ret;
}

void Graph::populateSubreddit(std::string name) {
    // name is the name of the subreddit, example: UIUC

    set<string> user_list = reader.getUserListFromSubRedditFile(name);
    for (set<string>::iterator it = user_list.begin(); it != user_list.end(); it++) {
        string u = *it;
        if (checked_users.find(u) != checked_users.end()) { 
            //if the user has already been checked and exists in the set of checked users, do nothing
        } else { //if the user has not yet been checked
            set<string> subreddits = reader.getSubRedditListFromUserFile(u);
            subreddits.insert(name);
            connectSubRedditList(subreddits);
            checked_users.insert(u);
        }
    }
}

Graph::SubReddit* Graph::retrieveSubreddit(string subName) {
    //start by checking if the subreddit already exists in our map
    Graph::SubReddit* sub = getSubReddit(subName);
    if(sub) {
        return sub;
    } else {
        //subreddit does not exist
        SubReddit* newSub = new SubReddit();
        newSub->name = subName;
        unique_subreddits.insert(pair<string, SubReddit*>(subName, newSub));
        return newSub; //return a pointer to the newly created subreddit struct
    }
}

Graph::SubReddit* Graph::getSubReddit(string subName) const {
    //start by checking if the subreddit already exists in our map
    map<string, SubReddit*>::const_iterator iterator = unique_subreddits.find(subName);
    if(iterator != unique_subreddits.end()) {
        //subreddit already exists
        return iterator->second;
    } else {
        //subreddit does not exist
        return NULL;
    }
}

int Graph::getUsers() const {
    return checked_users.size();
}

int Graph::getSubs() const {
    return read_subs.size();
}

int Graph::commonUsers(string sub1, string sub2) const {
    //get pointers to the two subs
    Graph::SubReddit* s1 = getSubReddit(sub1);
    Graph::SubReddit* s2 = getSubReddit(sub2);

    if(s1 && s2) { //make sure that both subreddits exist in the graph
        //check if the two are connected
        map<SubReddit*, int>::iterator iterator = s1->adjacent.find(s2);
        if(iterator != s1->adjacent.end()) { //a connection exists
            return iterator->second;
        } else { //a connection does not exist
            return 0;
        }

    } else { //if either subreddit does not exist in the graph, return -1
        return -1;
    }

}


void Graph::connectSubreddits(SubReddit* sub1, SubReddit* sub2) {

    //check if the two are already connected (assume that if sub1 is adjacent to sub2, sub2 is adjacent to sub1)
    map<SubReddit*, int>::iterator iterator = sub1->adjacent.find(sub2);
    if(iterator != sub1->adjacent.end()) { //the connection already exists
        //increment the int
        iterator->second++;
        sub2->adjacent.find(sub1)->second++;

        if(iterator->second > max_connection) {
            max_connection = iterator->second;
        }
    } else { //otherwise make a new connection
        sub1->adjacent.insert(pair<SubReddit*, int>(sub2, 1));
        sub2->adjacent.insert(pair<SubReddit*, int>(sub1, 1));
    }
}

// List version of addWeight, which call addWeight to all pairs in the list
void Graph::connectSubRedditList(set<string> subreddit_list) {
    vector<SubReddit*> subs;
    for(set<string>::iterator it = subreddit_list.begin(); it != subreddit_list.end(); it++) {
        subs.push_back(retrieveSubreddit(*it));
    }

    for(int i = 0; i < (int) subs.size(); i++) {
        for(int j = i + 1; j < (int) subs.size(); j++) {
            connectSubreddits(subs[i], subs[j]); //simple algoritm to connect each subreddit with each other
        }
    }
}

map<string, Graph::SubReddit*> Graph::getSubReddits() const {
    return unique_subreddits;
}


map<string, double> Graph::dijkstra(string start) {
    // Construct heap/priority queue
    map<string, double> output = map<string, double>();
    SubReddit* startPointer;
    vector<SubReddit*> restPointers; 
    for(map<string, SubReddit*>::iterator it = unique_subreddits.begin(); it != unique_subreddits.end(); it++) {
        if (it->first == start) {
            startPointer = it->second;
        } else {
            restPointers.push_back(it->second);
        }
    }
    PriorityQueue pq = PriorityQueue(startPointer, restPointers);
    // Start of Dijkstra
    while (!pq.isEmpty()) {
        cout << "Dijkstra remaining: " << pq.getSize() << '\n';
        SubReddit* node = pq.peakMin();
        double weight = pq.peakMinValue();
        pq.popMin();
        output[node->name] = weight;
        if (weight == -1) {
            continue;
        }
        for (map<SubReddit*, int>::iterator it = node->adjacent.begin(); it != node->adjacent.end(); it++) {
            if (output.find(it->first->name) == output.end()) {
                double newWeight = weight + (double) 1/ (double) it->second;
                double oldWeight = pq.getWeight(it->first);
                if (oldWeight == -1 || oldWeight > newWeight) {
                    pq.changeWeight(it->first, newWeight);
                }
            }
        }
    }
    return output;
}

void Graph::clear() {
    //iterates through the set of unique subreddits, deallocating each subreddit
    for(map<string, SubReddit*>::iterator it = unique_subreddits.begin(); it != unique_subreddits.end(); it++) {
        delete it->second;
    }

    //resets the private variables
    unique_subreddits = map<string, SubReddit*>();
    checked_users = set<string>();
    read_subs = set<string>();
    reader = FileReader();
    max_connection = 0;
}