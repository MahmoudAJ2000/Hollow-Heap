# Description
This is an implementation of the Hollow Heap data structure. Hollow Heaps are used to speed up Dijkstra’s shortest path algorithm 
and algorithms for undirected and directed minimum spanning trees. This project only demonstrates the hollow heap in Dijkstra’s algorithm.

# Time complexity
All heap operations take O(1) time except delete and delete-min which take O(logn) amortized time.
Dijkstra runs in O(|E|+|V|log|V|) time with a hollow heap.

# Resources
https://oar.princeton.edu/bitstream/88435/pr1fc1s/1/HollowHeapsProgramming.pdf
https://pdfs.semanticscholar.org/04d8/29be7a8f1956a239772e0daa94aef48f8860.pdf
https://github.com/UAPSPC/Code-Archive/blob/master/graph/dijkstra/dijkstra_min.cpp

# Instructions
1. shortestpath1.cpp includes the solution to the kattis problem shortestpath1: https://open.kattis.com/problems/shortestpath1
This solution uses this implementation of the hollow heap in dijkstra. output from this file has the same format as the kattis problem description.

2. Run "make" to compile code into an executable "dijkstra.out".
Test case format for dijkstra have a format similar to the kattis problem, but includes a single test case for each input.
First line starts with four integers n,m,q,s separated by single spaces. where n is the numbers of nodes in the graph, 
m the number of edges, q the number of queries and s the index of the starting node. Nodes are numbered from 0 to n−1.
Then follow m lines, each line consisting of three (space-separated) integers u, v and w indicating that there is an 
edge from u to v in the graph with weight w. Then follow q lines of queries, each consisting of a single integer.<br><br>
Example format for an input graph with queries:<br><br>
n m q s<br>
u_0 v_0 w_0<br>
u_1 v_1 w_1<br>
...<br>
u_m v_m w_m<br>
t_0<br>
t_1<br>
...<br>
t_q<br><br>
tests folder includes test cases each with a different number of nodes starting from 5 nodes to 10000 nodes:
- test5.in
- test10.in
- test100.in
- test500.in
- test1k.in
- test10k.in<br>
To run a test case, simply run the exceutable with the test case i.e. "./dijkstra.out < tests/test10k.in"
output from this file has the format "Distance from u to v is d" or "No path from u to v was found" for each query.

3. testHH.cpp has simple unit tests to demonstrate the correctness of the Hollow heap operations. Simply compile file
and run exceutable to run the tests. Output displays each operation that was performed in a unit test, along with the
current minimum key in the heap.

# Additional info
On kattis, it takes 0.08s for the solution to get accepted with a priority queue, while it takes 0.15s to get accepted with the hollow heap.
This is because Kattis does not use graphs large enough to demonstrate Hollow heaps' effeciency

# File Summary
dijkstra.cpp: includes Dijkstra's algorithm from the U of A programming club repo
generateTests.cpp: script I used to generate the test cases for dijkstra
hollowHeap.cpp: Hollow heap class implementation
hollowHeap.h: Hollow heap class header file
node.cpp: Node class implementation
node.h: Node class header file
item.cpp: item class implementation
item.h: item class header file
shortestpath1.cpp: solution to the kattis problem shortestpath1 with a hollow heap
testHH.pp: unit tests for the hollow heap operations
main.cpp: run dijkstra with the hollow heap on an input test case
