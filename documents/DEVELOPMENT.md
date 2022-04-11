## Project Meeting Minutes
## Group Members: khanhn2, larrylp2, mohanty7
---

#### <strong>Week:</strong>
November 1st - November 7th
#### <strong>Meeting Location:</strong>
ISR Lounge Area
#### <strong>Time:</strong>
6:00 PM - 7:20 PM
#### <strong>Summary:</strong>
This meeting we worked on our Final Project Proposal, while discussing the specifics of our project idea and potential applications of traversals. To complete the project, we decided to  outline the basic structure of our program, by detailing the contents included within our classes, and constructing methods that are necessary to access specific parts of data. There was also a discussion on the specific data structures that we wanted to implement, such as minHeap and maps. This week, we finished up our Team Contract and Final Project Proposal, writing both of them as Markdown files and committing them to our project repository.


---
#### <strong>Week:</strong>
November 8th - November 14th
#### <strong>Meeting Location:</strong>
ISR Lounge Area
#### <strong>Time:</strong>
6:00 PM - 7:20 PM
#### <strong>Summary:</strong>
For this meeting, we mainly discussed about the code we've written since last week, as well as discussing possible implementations about our graph constructor.
The main idea we want to implement is starting from our parent reddit, r/uiuc, and reading in all the subreddits based on each user. From there, we will make new nodes and create connections between r/uiuc and neighboring subreddits.

We have currently finished data gathering, and will now focus on updating the graph constructor, as well as creating tests for our written code. The outline for the graph constructor has been drafted, and a test folder has been made to place all the appropriate tests.

These are the following plans that we would like to address:
1. Change timeline to do BFS before dijkstra
2. Amend meetings to be remote to accommodate group members.

This week's work: 
Khanh: implement Dijkstra; Natasha: test graph constructor and BFS traversal; Larry: Graph constructor.

---
#### <strong>Week:</strong>
November 22th - November 28th
#### <strong>Meeting Location:</strong>
Discord
#### <strong>Time:</strong>
6:00 PM - 6:30 PM
#### <strong>Summary:</strong>
This week, we focused on the Graph class, where we implemented the constructor and its various inner methods. To improve performance, we discussed optimization solutions and made small changes within the constructor by having helper methods store its attributes. The constructor produces promising results, but we still need to test the output properly. For this to work, we also discussed how to make tests. We are also planning on splitting the work for making a visualization of the graph and hope to have mostly everything done by next Friday.


This week's work: 
Khanh: implement Dijkstra; Natasha: make tests for graph and BFS; Larry: implements BFS

---

#### <strong>Week:</strong>
November 29th - December 5th
#### <strong>Meeting Location:</strong>
Discord
#### <strong>Time:</strong>
6:00 PM - 6:20 PM
#### <strong>Summary:</strong>
This week, we made major progress on the project. First, we adjusted the constructor class, completed our BFS traversal, and implemented the Dijkstra's algorithm. Additionally, we started on our goal to create a force-directed diagram of the nodes, finishing a basic GraphVisualiztion class and starting on the PhysicsSimulation class. In the next week, we aim to complete the physics simulation and create tests for all of our existing classes. We hope to finish programming and debugging before the weekend so we can complete our final report and record our presentation.

---

#### <strong>Week:</strong>
December 6th - December 12th
#### <strong>Meeting Location:</strong>
Discord
#### <strong>Time:</strong>
6:00 PM - 6:20 PM
#### <strong>Summary:</strong>
This week was primarily focused on implementing the PhysicSimulation class, which would be responsible for emulating the simulation for our graph. After implementing the class constructor, most of the time was spent on creating methods that calculated new positions for our nodes. While running the simulation, we ran into several issues surrounding memory allocation. In order to fix the memory leak, we added optimizations within the PhysicSimulation class, where we changed the storage type of positions. Besides technical implementations of our code, we continued to work on completing our final project report. This included revising our development and goal drafts, as well as writing the results section of our final draft. During our meeting time, we spent time writing our scripts and recording our presentation.



