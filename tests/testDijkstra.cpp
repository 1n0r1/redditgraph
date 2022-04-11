#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

TEST_CASE("testDijkstra", "[weight=1]") {

    std::string file_path = "data/testDijkstra1/";

    Graph g = Graph(file_path);
    g.readGraphBFS("A");
    
    Graph::SubReddit* sA = g.retrieveSubreddit("A");
    Graph::SubReddit* sB = g.retrieveSubreddit("B");
    Graph::SubReddit* sC = g.retrieveSubreddit("C");
    Graph::SubReddit* sD = g.retrieveSubreddit("D");
    Graph::SubReddit* sE = g.retrieveSubreddit("E");
    REQUIRE((sA->adjacent)[sB] == 3);
    REQUIRE((sA->adjacent)[sC] == 2);
    REQUIRE((sA->adjacent)[sE] == 1);
    REQUIRE((sB->adjacent)[sA] == 3);
    REQUIRE((sB->adjacent)[sD] == 1);
    REQUIRE((sB->adjacent)[sE] == 2);
    REQUIRE((sD->adjacent)[sB] == 1);
    REQUIRE((sE->adjacent)[sB] == 2);
    REQUIRE((sE->adjacent)[sA] == 1);
    REQUIRE((sE->adjacent)[sC] == 5);
    REQUIRE((sC->adjacent)[sE] == 5);
    REQUIRE((sC->adjacent)[sA] == 2);

    map<string, double> output = g.dijkstra("A");
    
    REQUIRE(output["A"] == 0);
    REQUIRE(output["B"] == (double) 1/3);
    REQUIRE(output["C"] == (double) 1/2);
    REQUIRE(output["D"] == (double) 4/3);
    REQUIRE(output["E"] == (double) 7/10);
}