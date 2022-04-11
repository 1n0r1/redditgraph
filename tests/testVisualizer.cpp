#include "../GraphVisualization.h"
#include "../cs225/catch/catch.hpp"


TEST_CASE("Draw Nodes Simple Graph", "[weight=1]")
{
    //Simple graph with just two nodes, one at (4,5) and another at (5,17)
	Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";

    std::pair<int, int> position1(3000, 700);
    std::pair<int ,int> position2(750, 2680);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));

    GraphVisualization visual = GraphVisualization(4000, 3500, 2, "InterFontCharacters/");

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    REQUIRE(drawing->height() == 3500);
    REQUIRE(drawing->width() == 4000); 
    REQUIRE(drawing->getPixel(3000, 700).h == 11); //UIUC node automatically orange
    REQUIRE(drawing->getPixel(750, 2680).h == 180);
    delete uiuc;
    delete cs;
    delete drawing;
}

TEST_CASE("Draw Edges Simple Graph", "[weight=1]")
{
    //Simple graph with just two nodes, one at (4,5) and another at (5,17)
	Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";

    std::map<Graph::SubReddit*, int> adj;
    std::map<Graph::SubReddit*, int> adj2;
    adj2.insert({cs, 1});
    adj.insert({uiuc, 1});

    cs->adjacent = adj;
    uiuc->adjacent = adj2;

    std::pair<int, int> position1(3000, 700);
    std::pair<int ,int> position2(750, 2680);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));

    GraphVisualization visual = GraphVisualization(4000, 3500, 2, "InterFontCharacters/");

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    REQUIRE(drawing->height() == 3500);
    REQUIRE(drawing->width() == 4000); 

    //test that the midpoint is colored instead of tracing entire edge
    REQUIRE(drawing->getPixel((3000.0 + 750) / 2, (700.0 + 2680) / 2).l == 0.5);
    delete uiuc;
    delete cs;
    delete drawing;

}

TEST_CASE("Draw Nodes Larger Graph", "[weight=1]")
{
    Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";

    Graph::SubReddit* one = new Graph::SubReddit();
    one->name = "one";

    Graph::SubReddit* two = new Graph::SubReddit();
    two->name = "two";

    Graph::SubReddit* three = new Graph::SubReddit();
    three->name = "three";

    std::pair<int, int> position1(3000, 700);
    std::pair<int ,int> position2(750, 2680);
    std::pair<int ,int> position3(400, 300);
    std::pair<int ,int> position4(3000, 3000);
    std::pair<int ,int> position5(2000, 200);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(one, position3));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(two, position4));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(three, position5));

    GraphVisualization visual = GraphVisualization(4000, 4000, 4, "InterFontCharacters/");

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    REQUIRE(drawing->height() == 4000);
    REQUIRE(drawing->width() == 4000); 
    REQUIRE(drawing->getPixel(3000, 700).h == 11); //UIUC node automatically orange
    REQUIRE(drawing->getPixel(750, 2680).h != 0); 
    REQUIRE(drawing->getPixel(400, 300).h != 0); 
    REQUIRE(drawing->getPixel(3000, 3000).h != 0); 
    REQUIRE(drawing->getPixel(2000, 200).h != 0); 
    delete uiuc;
    delete cs;
    delete one;
    delete two;
    delete three;
    delete drawing;
}

TEST_CASE("Draw Edges Larger Graph", "[weight=1]")
{
    Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";
    
    std::map<Graph::SubReddit*, int> adj2;
    adj2.insert({cs, 1});

    Graph::SubReddit* one = new Graph::SubReddit();
    one->name = "one";
    std::map<Graph::SubReddit*, int> adj3;
    adj3.insert({cs, 1});

    Graph::SubReddit* two = new Graph::SubReddit();
    two->name = "two";
    std::map<Graph::SubReddit*, int> adj4;
    adj4.insert({cs, 1});

    Graph::SubReddit* three = new Graph::SubReddit();
    three->name = "three";
    std::map<Graph::SubReddit*, int> adj5;
    adj5.insert({cs, 1});
    adj5.insert({two, 1});
    adj4.insert({three, 1});

    std::map<Graph::SubReddit*, int> adj;
    adj.insert({uiuc, 1});
    adj.insert({one, 1});
    adj.insert({two, 1});
    adj.insert({three, 1});

    cs->adjacent = adj;
    uiuc->adjacent = adj2;
    one->adjacent = adj3;
    two->adjacent = adj4;
    three->adjacent = adj5;


    std::pair<int, int> position1(3000, 700);
    std::pair<int ,int> position2(750, 2680);
    std::pair<int ,int> position3(400, 300);
    std::pair<int ,int> position4(3000, 3000);
    std::pair<int ,int> position5(2000, 200);


    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(one, position3));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(two, position4));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(three, position5));

    GraphVisualization visual = GraphVisualization(4000, 4000, 4, "InterFontCharacters/");

    cs225::PNG* drawing = visual.drawGraph(redditCoords);
    drawing->writeToFile("smallVisualizerTestOutput.png");

    REQUIRE(drawing->height() == 4000);
    REQUIRE(drawing->width() == 4000); 


    //test the midpoints points of each edge
    REQUIRE(drawing->getPixel((3000.0 + 750) / 2, (700.0 + 2680) / 2).l == 0.5); //edge between UIUC and CS
    REQUIRE(drawing->getPixel((400.0 + 750) / 2, (300.0 + 2680) / 2).l == 0.5); //edge between one and CS
    REQUIRE(drawing->getPixel((2000.0 + 750) / 2, (200.0 + 2680) / 2).l == 0.5); //edge between two and CS
    REQUIRE(drawing->getPixel((2000.0 + 750) / 2, (200.0 + 2680) / 2).l == 0.5); //edge between three and CS
    REQUIRE(drawing->getPixel((3000.0 + 2000) / 2, (3000.0 + 200) / 2).l == 0.5); //edge between two and three


    //test hues
    REQUIRE(drawing->getPixel(3000, 700).h == 11); //UIUC node automatically orange
    REQUIRE(drawing->getPixel(750, 2680).h == 0); 
    REQUIRE(drawing->getPixel(400, 300).h == 135); 
    REQUIRE(drawing->getPixel(3000, 3000).h == 90); 
    REQUIRE(drawing->getPixel(2000, 200).h == 90); 

    delete uiuc;
    delete cs;
    delete one;
    delete two;
    delete three;
    delete drawing;

}

