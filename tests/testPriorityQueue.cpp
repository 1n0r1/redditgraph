#include "../PriorityQueue.h"
#include "../cs225/catch/catch.hpp"

TEST_CASE("testPriorityQueue", "[weight=1][part=1]") //Basic function
{
	PriorityQueue pq = PriorityQueue();

    Graph::SubReddit* p1 = new Graph::SubReddit();
    Graph::SubReddit* p2 = new Graph::SubReddit();
    Graph::SubReddit* p3 = new Graph::SubReddit();
    Graph::SubReddit* p4 = new Graph::SubReddit();
    Graph::SubReddit* p5 = new Graph::SubReddit();
    
    pq.push(p1, -1);
    pq.push(p2, 10);
    pq.push(p3, 1);
    pq.push(p4, 20);
    pq.push(p5, 7);

    vector<double> list;
    vector<double> expected;
    vector<Graph::SubReddit*> expectedPointers;

    expectedPointers.push_back(p3);
    expectedPointers.push_back(p5);
    expectedPointers.push_back(p2);
    expectedPointers.push_back(p4);
    expectedPointers.push_back(p1);

    expected.push_back(1);
    expected.push_back(7);
    expected.push_back(10);
    expected.push_back(20);
    expected.push_back(-1);
    int i = 0;
    while (!pq.isEmpty()) {
        list.push_back(pq.peakMinValue());
        REQUIRE(pq.peakMin() == expectedPointers[i]);
        pq.popMin();
        i++;
    }

    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    REQUIRE(list == expected);
}

TEST_CASE("testChangeWeight", "[weight=1][part=1]") //Test change weight
{
	PriorityQueue pq = PriorityQueue();

    Graph::SubReddit* p1 = new Graph::SubReddit();
    Graph::SubReddit* p2 = new Graph::SubReddit();
    Graph::SubReddit* p3 = new Graph::SubReddit();
    Graph::SubReddit* p4 = new Graph::SubReddit();
    Graph::SubReddit* p5 = new Graph::SubReddit();
    
    pq.push(p1, -1);
    pq.push(p2, 10);
    pq.push(p3, 1);
    pq.push(p4, 20);
    pq.push(p5, 7);

    pq.changeWeight(p4, 2);
    vector<double> list;
    vector<double> expected;
    vector<Graph::SubReddit*> expectedPointers;

    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(7);
    expected.push_back(10);
    expected.push_back(-1);

    expectedPointers.push_back(p3);
    expectedPointers.push_back(p4);
    expectedPointers.push_back(p5);
    expectedPointers.push_back(p2);
    expectedPointers.push_back(p1);

    int i = 0;
    while (!pq.isEmpty()) {
        list.push_back(pq.peakMinValue());
        REQUIRE(pq.peakMin() == expectedPointers[i]);
        pq.popMin();
        i++;
    }
    REQUIRE(list == expected);
    
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
}

TEST_CASE("testSpecialCases", "[weight=1][part=1]") //Test special cases
{
	PriorityQueue pq = PriorityQueue();

    Graph::SubReddit* p1 = new Graph::SubReddit();
    Graph::SubReddit* p2 = new Graph::SubReddit();
    Graph::SubReddit* p3 = new Graph::SubReddit();
    Graph::SubReddit* p4 = new Graph::SubReddit();
    Graph::SubReddit* p5 = new Graph::SubReddit();
    
    pq.push(p1, -1);
    REQUIRE(pq.peakMinValue() == -1);
    pq.changeWeight(p1, 5);
    REQUIRE(pq.peakMinValue() == 5);
    
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
}