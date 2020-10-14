# Pathfinding Algorithms' Visualizer
A* , Best First Search , Dijkstra , BFS , BiBFS , DFS 

---

## Notes 

* First, choose the source node "Colored green"
* Then, choose the destination node "Colored blue"
* After that, you can choose any number of nodes to be blocks "Colored red" except the starting and ending nodes
* Press
  * 'A' to run A* 
  * 'T' to run Best First Search
  * 'J' to run Dijkstra
  * 'B' to run BFS
  * 'I' to run BiBfs
  * 'D' to run DFS
* If there is a path from the source to the destination,
  * After running DFS, the destination node will be colored yellow
  * After running any other algorithm, all the nodes in the path will be colored yellow showing the exact shortest path
* Wait until the current algorithm's visualization is finished
* Then
  * If you want to run another algorithm on the same maze, press the letter of the wanted algorithm
  * press 'R' to reset the maze
* change sleepingTime constant variables accordingly to increase/decrease the speed of the visualization of an algorithm or the speed backtracking the path
* It should be noted that shortest path algorithms here can simply be replaced by BFS because there is no weights, but the main purpose is to visualize the algorithms and get a better understanding of how they work.