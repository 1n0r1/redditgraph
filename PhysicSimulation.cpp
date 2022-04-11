#include "PhysicSimulation.h"
#include <cmath>
#include <fstream>

PhysicSimulation::PhysicSimulation() {
    time = 0;
}

void PhysicSimulation::initiateGraph(Graph& g) {

    //retrieve the collection of subreddits
    map<string, Graph::SubReddit*> subreddits = g.getSubReddits();
    //setting the common position
    float x = 0;
    float y = 0;
    //for each subreddit, we insert the value with 
    for(map<string, Graph::SubReddit*>::iterator it = subreddits.begin(); it != subreddits.end(); it++) {
        //check to make sure each entry is not null
        x++;
        if (x >= sqrt(g.getSubs())) {
            y++;
            x = 0;
        }
        if (it -> second != NULL) {
            positions.insert(pair<Graph::SubReddit*, pair<float, float>>(it -> second, make_pair(x,y)));
        }
    }
    
}

map<Graph::SubReddit*, pair<float, float>> PhysicSimulation::simulateFor(int seconds) {
    map<Graph::SubReddit*, pair<float, float>> new_positions;


    float W = 200000;
    float L = 200000;
    float area = W*L;
    float k = sqrt(area/positions.size());
    //loop through the amount of seconds
    for (int i = 0; i < seconds; i++) {
        time += 0.01;
        cout << "Simulating Second: " << i + 1 << endl;
        for (map<Graph::SubReddit*, pair<float, float>>::iterator it = positions.begin(); it != positions.end(); it++) {
            
            //finding individual coordinates for current node
            float cX = it -> second.first;
            float cY = it -> second.second;

            //create our force vector
            std::pair<float, float> force_vector(0, 0);

            //create a subreddit pointer for traversing adjacent nodes
            Graph::SubReddit* subPtr = it -> first;

            //loop through adjacent nodes map
            for (map<Graph::SubReddit*, int>::iterator n = subPtr -> adjacent.begin(); n != subPtr -> adjacent.end(); n++) {
                //need to find the position vector for the adjacent node
                Graph::SubReddit* ptr = n -> first;

                map<Graph::SubReddit*, pair<float, float>>::iterator iter = positions.find(ptr);
                float aX = iter -> second.first;
                float aY = iter -> second.second;
                float squared_x = pow(aX - cX, 2);
                float squared_y = pow(aY - cY, 2);
                float distance = sqrt(squared_x + squared_y);
                std::pair<float, float> unit_vector;
                if (distance == 0) {
                    srand(rand());
                    int angle = rand();
                    unit_vector = make_pair(cos(angle),sin(angle));
                } else {
                    unit_vector = make_pair((aX - cX) / distance, (aY - cY)/distance);
                }
                //compute spring force vector formula

                // Fruchterman & Reingold Model
                float spring_force_value_x = distance*distance/(k/n->second*1000) * unit_vector.first;
                float spring_force_value_y = distance*distance/(k/n->second*1000) * unit_vector.second;
                
                //update the force vector
                force_vector.first += spring_force_value_x;
                force_vector.second += spring_force_value_y;
            }

            for (map<Graph::SubReddit*, pair<float, float>>::iterator itt = positions.begin(); itt != positions.end(); itt++) {
                if (itt->first == it->first) continue;
                float aX = itt -> second.first;
                float aY = itt -> second.second;
                float squared_x = pow(aX - cX, 2);
                float squared_y = pow(aY - cY, 2);
                float distance = sqrt(squared_x + squared_y);

                std::pair<float, float> unit_vector;
                if (distance == 0) {
                    srand(rand());
                    int angle = rand();
                    unit_vector = make_pair(cos(angle),sin(angle));
                    distance = 0.0001;
                } else {
                    unit_vector = make_pair((aX - cX) / distance, (aY - cY)/distance);
                }

                float spring_force_value_x = -0.000001*k*k/distance * unit_vector.first;
                float spring_force_value_y = -0.000001*k*k/distance * unit_vector.second;

                //update the force vector
                force_vector.first += spring_force_value_x;
                force_vector.second += spring_force_value_y;
            }

            //insert all the data into our newly created map
            new_positions[it -> first].first = exp(-time/10000000)*force_vector.first + cX;
            new_positions[it -> first].second = exp(-time/10000000)*force_vector.second + cY;

            if (new_positions[it -> first].first > 100000) {
                new_positions[it -> first].first = 100000;
            }
            if (new_positions[it -> first].second > 100000) {
                new_positions[it -> first].second = 100000;
            }
            if (new_positions[it -> first].first < -100000) {
                new_positions[it -> first].first = -100000;
            }
            if (new_positions[it -> first].second < -100000) {
                new_positions[it -> first].second = -100000;
            }
        }
        positions = new_positions;
    }
    return positions;
}
