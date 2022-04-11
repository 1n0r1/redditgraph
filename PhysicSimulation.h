#include "Graph.h"

class PhysicSimulation {
    public:
        PhysicSimulation();

        void initiateGraph(Graph &g);
        map<Graph::SubReddit*, pair<float, float>> simulateFor(int seconds);
        
    private:
        float time;
        map<Graph::SubReddit*, pair<float, float>> positions;
};
