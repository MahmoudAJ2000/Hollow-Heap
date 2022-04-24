// code from U of A programming club repo: https://github.com/UAPSPC/Code-Archive/blob/master/graph/dijkstra/dijkstra_min.cpp
#include <vector>
#include <list>
#include <limits>
#include <queue>
#include <functional>
#include <utility>
#include "item.cpp"
#include "node.cpp"
#include "hollowHeap.cpp"

using namespace std;

struct Graph {
	Graph(int N) : graph(N, list<pair<int, int> >()) {}
	void addEdge(int src, int dst, int len) { graph[src].push_back(make_pair(dst, len)); }
	vector<list<pair<int, int> > > graph;
};

// Dijkstra with a hollow heap
vector<int> DijkstraHH(const Graph& G, int src){

	vector<bool> visited(G.graph.size(), false);
	vector<int> distance(G.graph.size(), numeric_limits<int>::max());
	vector<int> prev(G.graph.size(), -1);
	vector<Node<pair<int,int>>*> nodes(G.graph.size());

    HollowHeap<pair<int,int>> HH;

	
    auto i = G.graph.size();
	for (i=0; i<G.graph.size();++i){
		if (i==src){
			distance[src] = 0;
			nodes[src] = HH.insert(make_pair(0, src));
			continue;
		}
		nodes[i] = HH.insert(make_pair(numeric_limits<int>::max(),i));
	}
	
	while (!HH.isEmpty()) {
		pair<int, int> entry = HH.findMin(); HH.deleteMin();
		int cur = entry.second;
		if (visited[cur]) continue;
		for (list<pair<int, int> >::const_iterator it = G.graph[cur].begin(); it != G.graph[cur].end(); ++it) {
			if (visited[it->first]) continue;
			if (distance[cur] + it->second < distance[it->first]) {
				distance[it->first] = distance[cur] + it->second;
				prev[it->first] = cur;
                if (nodes[it->first]->isHollow()) HH.insert(make_pair(distance[it->first], it->first));
				else nodes[it->first] = HH.decreaseKey(nodes[it->first],make_pair(distance[it->first], it->first)); 
			}
		}
		visited[cur] = true;
	}
	return distance;
}
