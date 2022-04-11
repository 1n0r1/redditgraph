#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Graph.h"
#include "GraphVisualization.h"

int main() {
    bool exit = false;
    while (exit == false) {
        cout << "Enter data directory..." <<'\n';
        string dir;
        cin >> dir;
        
        Graph g1 = Graph(dir);
        cout << "Enter starting node..." << '\n';
        string start;
        cin >> start;
        g1.readGraphBFS(start);
        while (true) {
            cout << "What you want to do? Dijkstra/BFS/Visualization/Switch/Exit" << '\n';
            string command;
            cin >> command;
            string output_lo;
            if (command != "Exit" && command != "Switch")
            {
                cout << "Enter output location..." << '\n';
                cin >> output_lo;
            }
            if (command == "Visualization") {
                cout << "Enter seconds to simulate..." << '\n';
                int step;
                cin >> step;
                cout << "Enter output picture size (two integer)" << '\n';
                int x, y;
                cin >> x >> y;
                cout << "Creating Visualization class" << endl;
                GraphVisualization visual = GraphVisualization(x, y, g1.getMaxConnection(), "InterFontCharacters/");
                cout << "Constructing Simulator" << endl;
                PhysicSimulation sim = PhysicSimulation();
                cout << "Initiating Simulator" << endl;;
                sim.initiateGraph(g1);
                cout << "Starting Simulation" << endl;
                map<Graph::SubReddit*, pair<float, float>> positions = sim.simulateFor(step);
                cout << "Converting Coordinates" << endl;
                map<Graph::SubReddit*, pair<int, int>> convertedCoords = visual.convertCoordinates(positions);
                cout << "Drawing Graph" << endl;
                cs225::PNG* image = visual.drawGraph(convertedCoords);
                image->writeToFile(output_lo);
                delete image;
            }
            if (command == "Dijkstra") {
                cout << "Enter starting point..." << '\n';
                string ss;
                cin >> ss;
                map <string, double> dijkstra = g1.dijkstra(ss);
                vector<pair<string, double>> v = vector<pair<string, double>>();
                for (auto itr : dijkstra) {
                    v.push_back(std::make_pair(itr.first, itr.second));
                }
                struct lessthan {
                    inline bool operator() (const pair<string, double>& p1, const pair<string, double>& p2) {
                        if (p1.second == -1) {
                            return false;
                        }
                        if (p2.second == -1) {
                            return true;
                        }
                        return (p1.second < p2.second);
                    }
                };
                std::sort(v.begin(), v.end(), lessthan());
                ofstream Dijkstra(output_lo);
                for(auto itr : v) {
                    Dijkstra << itr.first << " " << itr.second << '\n';
                }                
            }
            if (command == "BFS") {
                cout << "Enter starting point..." << '\n';
                string ss;
                cin >> ss;
                vector<string> v = g1.BFSTraversal(ss);
                ofstream BFS(output_lo);
                for(auto itr : v) {
                    BFS << itr << '\n';
                }    
            }
            if (command == "Switch") {
                break;
            }
            if (command == "Exit") {
                exit = true;
                break;
            }
        }
    }
    
    return 0;
}