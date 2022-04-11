#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

TEST_CASE("Constructor Simple Graph 1", "[weight=1]") {
    std::string file_path = "data/testConstructor/";

    Graph g = Graph(file_path);
    g.readGraphBFS("one");
    
    REQUIRE((g.commonUsers("two", "one") == 2 && g.commonUsers("one", "two") == 2));
    REQUIRE((g.commonUsers("three", "one") == 1 && g.commonUsers("one", "three") == 1));
    REQUIRE((g.commonUsers("four", "one") == 1 && g.commonUsers("one", "four") == 1));
    REQUIRE((g.commonUsers("five", "one") == 1 && g.commonUsers("one", "five") == 1));
    REQUIRE((g.commonUsers("three", "two") == 1 && g.commonUsers("two", "three") == 1));
    REQUIRE((g.commonUsers("four", "two") == 1 && g.commonUsers("two", "four") == 1));
    REQUIRE((g.commonUsers("five", "two") == 1 && g.commonUsers("two", "five") == 1));
    REQUIRE((g.commonUsers("four", "three") == 1 && g.commonUsers("three", "four") == 1));
    REQUIRE((g.commonUsers("five", "three") == 0 && g.commonUsers("three", "five") == 0));
    REQUIRE((g.commonUsers("five", "four") == 0 && g.commonUsers("four", "five") == 0));
}

TEST_CASE("Constructor Simple Graph 2", "[weight=1]") {
    std::string file_path = "data/testDijkstra1/";

    Graph g = Graph(file_path);
    g.readGraphBFS("A");
    
    Graph::SubReddit* sA = g.retrieveSubreddit("A");
    Graph::SubReddit* sB = g.retrieveSubreddit("B");
    Graph::SubReddit* sC = g.retrieveSubreddit("C");
    Graph::SubReddit* sD = g.retrieveSubreddit("D");
    Graph::SubReddit* sE = g.retrieveSubreddit("E");
    REQUIRE((g.commonUsers("B", "A") == 3 && g.commonUsers("A", "B") == 3));
    REQUIRE((g.commonUsers("C", "A") == 2 && g.commonUsers("A", "C") == 2));
    REQUIRE((g.commonUsers("D", "B") == 1 && g.commonUsers("B", "D") == 1));
    REQUIRE((g.commonUsers("E", "B") == 2 && g.commonUsers("B", "E") == 2));
    REQUIRE((g.commonUsers("A", "E") == 1 && g.commonUsers("E", "A") == 1));
    REQUIRE((g.commonUsers("C", "E") == 5 && g.commonUsers("E", "C") == 5));
}


TEST_CASE("BFS Output Simple Graph 1", "[weight=1]") {
    std::string file_path = "data/testConstructor/";

    Graph g = Graph(file_path);
    g.readGraphBFS("one");

    vector<string> bfs = g.BFSTraversal("one");

    vector<string> expected = {"one", "five", "four", "three", "two"};

    REQUIRE(expected == bfs);
}

TEST_CASE("BFS Output Simple Graph 2", "[weight=1]") {
    std::string file_path = "data/testDijkstra1/";

    Graph g = Graph(file_path);
    g.readGraphBFS("A");

    vector<string> bfs = g.BFSTraversal("A");

    vector<string> expected = {"A", "B", "C", "E", "D"};

    REQUIRE(expected == bfs);
}

