# Reddit Graph

![](/images/larry_output.png "Larry Graph")
### Main features:
<ul>
    <li>Graph visualization and regional coloring</li>
	<li>Path finding to find relation between two subreddits. </li>
	<li>Recommendations for similar subreddits</li>
</ul>

### Dataset Acquisition and Processing:
All of our data will be collected through the reddit API. The collected data will be stored in json files and manipulated with C++. Each subreddit will be represented by a node, with edges drawn between subreddits with common users. The strength of a connection between two subreddits will be the number of common accounts that comment and post on both pages.  

### Graph Algorithms:
The specific kinds of graph algorithms we will be implementing include Breadth-First-Search (BFS) Traversal, Dijkstra’s Algorithm and a Graphic Output of the results. 

#### BFS Traversal:
Use this level order traversal to display subreddit hierarchy, with the subreddits more related to r/UIUC appearing earlier in the traversal.
#### Dijkstra:
Find the optimal path between two subreddits and output the smallest total weight to show the relationship between two subreddits.
#### Graphic output:
Use the generated graph and output an image using force-directed graph drawing. <br>
Maybe some coloring by finding closely related region


## The location of all major code, data, and results

/cs225 : Contains the cs225 library that involves PNG, testing, make

/data-fetching : Contains code used in fetching data
* /data-fetching/data : The result from the data fetching
* /data-fetching/data/converter.py : Convert .json files to .txt
* /data-fetching/data/fetch_data.py : Main data-fetching code
* /data-fetching/data/fetch_from_subreddit.py : Code that reads from one subreddit
* /data-fetching/data/fetch_from_user.py : Convert Code that reads from one user
* /data-fetching/data/get-token.py : Get the access token neccessary to fetch data from reddit

/data : Contains all the datasets, including the test data
* /data/data1/ : Fetched data containing about 900 nodes
* /data/data2/ : Fetched data containing about 60000 nodes
* /data/testConstructor : Test data to test the graph constructor
* /data/testDijkstra1 : Test data to test the Dijkstra algorithm

/documents : Contains all the documents
* /documents/meeting_records.md : Log of meeting records/DEVELOPMENT file
* /documents/project_proposal.md : Project proposal/GOALS file
* /documents/results_report.md : Two page final report with the final project deliverables/RESULTS file
* /documents/team_contract.md : Team contract

/images : Contains image resources used in the final report
    
/InterFontCharacters : Contains individual PNGs for alphanumeric characters from the open source Inter font family

/tests : Contains all test suites used in testing

FileReader.cpp FileReader.h : File reader class, use to read from datasets

Graph.cpp Graph.h : The main graph class

GraphVisualization.cpp GraphVisualization.h : Class used to output visualization image

PhysicSimulation.cpp PhysicSimulation.h : Physics Simulation class use to output the final coordinates of all nodes to give to GraphVisualization for it to draw

PriorityQueue.cpp PriorityQueue.h : Pointer-based min heap for Dijkstra

## Building and running the executable
To build the program:
`make graph`

To run the program:
`./graph`

You will then be entered into our advanced UI environment. Enter the input directory and the starting node to read from the dataset.

![image](https://media.github-dev.cs.illinois.edu/user/11993/files/cab1515d-3e7f-46d4-adc3-602dd4868870)

![image](https://media.github-dev.cs.illinois.edu/user/11993/files/7e919c69-093f-4ce3-91d7-74924ee25121)

Then it will ask you what you want to do. Enter the command correspondingly:

`Dijkstra`

![image](https://media.github-dev.cs.illinois.edu/user/11993/files/ed14d428-f80d-4c4a-bfdb-7f90b4a5823a)

Enter the command, then the output location and the starting point. The output will look like this

![image](https://media.github-dev.cs.illinois.edu/user/11993/files/791adaa9-4250-4985-9e80-745fc60fe1a1)

with the number next to each corresponse to the distance from the starting node

`BFS`

![image](https://media.github-dev.cs.illinois.edu/user/11993/files/d6a9454f-f71a-41c0-b3ea-244c12048438)

Enter the command, then the output location and the starting point. The output will look like this

![image](https://media.github-dev.cs.illinois.edu/user/11993/files/22fb8991-3857-4d93-92f4-d52318c37d0f)

`Visualization`

![image](https://media.github-dev.cs.illinois.edu/user/11993/files/7c7d0e4c-d5bb-4f52-8454-46a251b48522)

Enter the command, followed by the output location, then the seconds to simulate, typically from 1000 to 2000, and enter picture size

`Switch`

Switch to another graph. The current graph will be erased and you can enter the directory to a new dataset

`Exit`

Exit the program

## Testing
To build the test:
`make testgraph`

To run the test:
`./testgraph`

There is also an output image after running the test. It should looks like this:
![smallVisualizerTestOutput](https://media.github-dev.cs.illinois.edu/user/11993/files/18cbb9c8-ff8c-4256-9e88-b75bd75758c6)


We created tests for all of our features. All tests read in a small dataset we created and calculated. Dijkstra and BFS test will test whether the output is as we expected from our own calculation of shortest paths. The constructor will test both the read function and the graph constructor, testing whether the graph formed the structure we intended, with the right weight all edges are two directional. There is also FileReader test which tests whether the FileReader read correctly, not missing any line and ignore empty lines. PriorityQueue test tests for basic functionality of the PriorityQueue. For the Visualizer test, we test if the output images changes the pixels at the locations that we wanted or not. For the PhysicSimulation class, we output the image, look at the image and adjust the physics model correspondingly. There are no test for this class and we just tune it so that it can output a pretty image.
