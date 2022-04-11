## <strong>CS 225 Final Project Proposal</strong>
## Group Members: khanhn2, larrylp2, mohanty7
--- 
### <strong>Leading Question:</strong>
What subreddits are redditors of the University of Illinois at Urbana Champaign most active on, and how are these subreddits related? 

The goal of this project is to measure how closely subreddits are related to each other, starting from the r/UIUC subreddit and branching out to other related subreddits. To measure the relationship between two subreddits, we will find all the commenters in the subreddit, look at each commenter’s profile to see which other subreddits they comment on, and establish an edge between those subreddits. This will hopefully recommend to similar r/UIUC users new subreddits.

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


| Week | Deliverable Tasks |
|------|-------------------|
|November 8th - November 14th| <li> Look into and begin collecting data using the Reddit API </li> <li>Create basic outline for graph data structure to store data </li>|
|November 15th - November 21st| <li>Read collected data into a graph </li><li>Implement Dijkstra to find optimal path between 2 nodes</li> <li>Create some tests for data acquisition and creating graph from data</li>|
|November 22nd - November 28th| <li>Implement BFS</li><li>Create tests for BFS</li><li>Work on mid-project report</li> |
|November 29th - December 5th|<li>Implement graphic output of the graph</li><li>Create tests for graphic output</li>|
|December 6th - December 12th|<li>Make the final presentation and deliverables</li>|


