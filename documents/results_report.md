# Final Project Report

## Data Collection and Graph

The first is our graph implementation and constructor. The format of our collected Reddit data heavily influenced our initial approach to graph construction. Each data set will be a folder containing two folders, /subreddit_text and /user_text. Each file in /subreddit_text will be named as the subreddit_name.txt and each line in the file will contain a user name. Similarly, each file in /user_text will each be named as user_name.txt and each line in that file will contain a subreddit name the user uses.

| ![](/images/subredditfile.png "SubReddit data file") | ![](/images/userfile.png "User data file") |
|----|---|
| /subreddit_text/somesub.txt | /user_text/someone.txt|


As such, we decided to represent each subreddit as a node struct initialized on the heap. Within our Graph class itself is a map of all unique subreddits we have initialized, with the key as the name of the subreddit and the value as the pointer to the subreddit in memory.

Each subreddit node contains its name and a map of adjacent subreddits. Since any two subreddits can share more than one user, we store the number of shared users between any two adjacent subreddits as the values of the map while the keys are the pointers to the adjacent subreddit nodes.

We construct this graph starting from the “UIUC.txt” subreddit file as our data collection also started from this initial subreddit. From here, we load in the UIUC.txt file and look at every user stored within, visiting each corresponding user_name.txt file in the /user_text/ file. Here, we draw connections between our starting subreddit and all of the subreddits that are under the same user_name.txt file. Then, the process continues in a breadth-first fashion as each newly visited adjacent node is added to a queue of subreddit files to check and a set of subreddits that have already been read.

From this constructed graph on our large dataset, we see that we have initialized around 62,962 subreddit nodes and have tracked 52,321 users. The two subreddits that share the most users are r/AskReddit and r/pics with 4537 shared users in the data we collected.

---

## Dijkstras
For Dijkstra, we implemented a pointer-based min heap for the algorithm so the weight can be changed and updated quickly in O(log(n)) time. Our function takes in a starting location and outputs the minimum distances from that location to all other nodes. This way, we can rank other subreddits in how much it is related to our starting node, in this case, r/UIUC.

The result of Dijkstra starting from r/UIUC shows that the top most commonly used subreddits among UIUC users are AskReddit, pics, memes, etc. which are all popular subreddits so its makes sense. Other than that, r/college is 101th, r/chicago is 159th, r/Champaign is 303th, r/UIUC_CS is 839th, 

---

## BFS Traversal
For our BFS, we used a queue to manage the next nodes to visit and a set to manage the nodes we have already visited. We start our BFS from the UIUC subreddit node, and move through the adjacent subreddits. We encountered an issue where although the BFS results between runs are correct, each level is output in a slightly different order. As such, we decided to go through each node’s adjacent nodes alphabetically to preserve order between runs and improve testability.

---

## Force Directed Diagram Visualization
Our final deliverable is our Visualization. To create a proper visualization, we split the process into two classes: GraphVisualization and PhysicSimulation. The GraphVisualization class handles the drawing of the nodes and edges while the PhysicSimulation class handles the physics calculations to generate positions for a Force Directed Diagram.

### Graph Visualization
The GraphVisualization class takes in a map of subreddit node pointers as keys and their positions as values. First, it converts the coordinates to be usable in a png. This process starts by translating all of the positions to be non-negative and not too far from 0,0. Then, it scales each coordinate to fit nicely within the bounds of the desired image.

Next, it draws all of the edges in a BFS traversal before drawing all of the nodes. To create labels for each subreddit node in the visualization, we created individual character pngs from the free open source Inter font family. With these individual character pngs, we build the labels for each node in the PNG file based on the subreddit name, resizing if necessary. We color different nodes based on their total weight. Nodes colored in red are the most popular subreddits with the most outgoing connections while nodes colored in blue are the least popular.

### Physics Simulation
For the PhysicSimulation class, we tried many different physics models. The first of which was a model that treats each connection between adjacent nodes as a spring, with the weight of that edge determining the spring's natural length or coefficient. From here we calculated the displacement force between each adjacent node using Hooke’s law, updating positions for each node at once between time steps. 

Since real life physics are continuous while computer simulation is step by step, we needed to take into consideration the size of the steps between frames. If the steps are too large, the nodes will overshoot, causing distances to become larger and larger until it continues overshooting with even greater force and go to infinity. If the steps are too small, the simulation will result in too little changes between each step, and the simulation will take too long. We decided to settle on changing the step size throughout the simulation, with the step size following the e^(-t/a) function, which will result in smaller and smaller step size as time goes on. By changing the a-variable we can change the rate at which the step size decreases. By using this, we get the best of both worlds: the simulation will not take 2 years to finish and the nodes will not overshooting each other to infinity since even if they overshoot for the few first steps, the following steps will get smaller and smaller and nodes will eventually close in on each other.

Additionally, we decided to use our smaller dataset of 900 nodes instead of the main data of 60000 nodes because of the simulation’s runtime, taking O(m) for each step (m is the number of edges). Thus we can’t run the simulation for large enough steps and the resulting graph only changes minimally:

![](/images/60000nodeoutput.png "60000 Nodes") 

60000 nodes data, initiated in a square formation, spring-only model, simulated for 20 steps, constant step of size 1

Thus we decided to use our 900 nodes data. However, the spring-only model doesn’t yield a very good result for this either.

![](/images/spring100steps.png "900 nodes spring only")

900 nodes data, initiated in a square formation, spring-only model, simulated for 100 steps, constant step of size 1

![](/images/spring1000stepsreducedquality.png "900 nodes spring only 2")

The spring-only model forced low-weighted nodes to be concentrated in the center, pushed by nodes all around them. We decided to add a repulsive force applied to all the nodes that originated at the origin, roughly following Coulomb’s law. But the graph tends to be shifted to one side since the Coulomb’s law origin doesn’t always follow the center of the graph.

Therefore we decided to use another model, Fruchterman and Reingold’s model. We found a paper: [Handbook of Graph Drawing and Visualization (brown.edu)](http://cs.brown.edu/people/rtamassi/gdhandbook/) and in chapter 12, there is the pseudo-code for the algorithm by Fruchterman and Reingold. We were initially apprehensive about this model since the algorithm complexity is O(m + n^2), which takes much longer time when we first use it on our graph of 60000 nodes. However, since we decided to use the 900 nodes graph for visualization, we can use the Fruchterman and Reingold model. However, this model and many others we found do not take into consideration edge weight between two nodes, so we decided to modify the equations to account for the weight between each node. For the attractive force, we multiplied the original equation by the weight, and divided by a constant, let's call this k. The reason for the divided constant is because our weight ranges from 1 to 5000, and we don’t want the 5000-weight to output 5000 times the force compared to the 1-weight. For the repulsive force, we divided the original by k\*1000 to account the attractive force being divided by k. We tried different ratio between the repulsive force and the attractive force and found that dividing the attractive force by k\*1000 yeilds the best result.

![](/images/F_R10000stepsreducedquality.png "10000 steps")

This time, we can clearly see clusters of nodes, and each of these clusters corresponds to a common group of subreddits that many people have in common. For example, one of the clusters in the following pictures is a group of crypto currencies subreddit. We were really happy with this result and decided to move forward using this model.

![](/images/similarsubreddits.png "Subreddit cluster")

---
## Tests
We do various tests to ensure that the behavior of our classes and methods are as expected. We created two smaller and simpler test datasets to test our data. We tested Dijkstra's, BFS, Graph Construction, and Graph Visualization using these tests.

To test BFS, we constructed graphs with smaller test datasets and compared the actual BFS output from our method with the expected BFS outputs from drawing the test graphs by hand.

To test the Graph Constructor, we constructed graphs and ensured that the number of shared users between Subreddits are correct.

To test the Visualization, we made basic visualizations from positions and checked if the output png has specific points colored (middle of a node, midpoint of edges).

To test the Dijkstra algorithm, we created a small test suite to test whether it outputs the correct distance according to our own calculation. We also created a badDijkstra version, which run really slow but is fundamentally correct, and diff the output of our Dijkstra and the badDijkstra, and the result is absolutely identical. This way we confirmed the correctness of our Dijkstra implementation.

To test the PriorityQueue, we created a small test that tests the basic functionality of it and it passes everything. The identical result between Dijkstra, which uses PriorityQueue, and badDijkstra, which doesn’t use PriorityQueue, also confirm the correctness of PriorityQueue.

---
## Discoveries


--- 
## Project Presentation
[Here](https://youtu.be/uCpAovuVFHs) is a link to our final project presentation.