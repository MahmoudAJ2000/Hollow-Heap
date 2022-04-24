#include <iostream>
#include <limits>
#include <time.h>
#include "dijkstra.cpp"

using namespace std;
using ll = long long;


int main(void){
    
    // Hollow heap object
    HollowHeap<int>  HH;

    // n: number of nodes (nodes are numbered from 0 to n-1)
    // m: number of edges
    // q: number of queries
    // s: starting node
    ll n,m,q,s;

    // cout << "Input graph to compute distances: " << endl;
    
    cin >> n >> m >> q >> s;

    Graph g(n);
    vector<ll> targets(q);

    while(m--){

        ll u,v,w;
        cin >> u >> v >> w;

        // add edge from u to v with weight w
        g.addEdge(u,v,w);
    }

    // get distances array
    vector<int> dist = DijkstraHH(g,s);

    for (ll i=0; i<q; ++i){
        cin >> targets[i];
    }

    // output distances
    for (const int &t: targets){
        if (dist[t] == numeric_limits<int>::max() || dist[t] < 0) cout << "No path from " << s << " to " << t << " was found" << endl;
        else cout << "Distance from " << s << " to " << t << " is " << dist[t] << endl;
    }

    return 0;
}
