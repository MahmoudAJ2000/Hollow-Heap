// Solution to kattis problem with hollow heap and dijkstra
// problem: https://open.kattis.com/problems/shortestpath1
#include <bits/stdc++.h>

using namespace std;

struct Graph {
	Graph(int N) : graph(N, list<pair<int, int> >()) {}
	void addEdge(int src, int dst, int len) { graph[src].push_back(make_pair(dst, len)); }
	vector<list<pair<int, int> > > graph;
};

template <typename T> class Node;

template <typename T>
class Item{

        public:

            // Constructors
            Item();
            Item(Node<T>* node);
            Item(Item<T>* item);

            // Assignment operator
            Item<T>& operator=(Item<T>* item);

            // Getter
            Node<T>* getNode();

            // Setter
            void setNode(Node<T>* node);

        private:

            // Pointer to the node that holds this item
            Node<T>* node;
};

template <typename T>
Item<T>::Item():node(nullptr){}

template <typename T>
Item<T>::Item(Node<T>* node){
    this->node = node;
}

template <typename T>
Item<T>::Item(Item<T>* item){
    this->node = item->getNode();
}

template <typename T>
Item<T>& Item<T>::operator=(Item<T>* item){
    this->node = item->getNode();
    return *this;
}

template <typename T>
Node<T>* Item<T>::getNode(){
    return this->node;
}

template <typename T>           
void Item<T>::setNode(Node<T>* node){
    this->node = node;
}

template <class T>
class Node{
    public:

        // Constructors
        Node();
        Node(Item<T>* e, const T& k);

        // == operator
        bool operator==(const Node<T>& lhs);

        // Getters
        T& getKey();
        Item<T>* getItem();
        long long& getRank();
        Node<T>* getChild();
        Node<T>* getNext();
        Node<T>* getEp();

        // Setters
        void setKey(T& key);
        void setItem(Item<T>* item);
        void setRank(long long& rank);
        void setChild(Node<T>* child);
        void setNext(Node<T>* next);
        void setEp(Node<T>* ep);

        // if hollow, return true
        bool isHollow();
  
    private:
        
        // if item is null, this node is hollow; otherwise, it is full.
        Item<T>* item; 

        // Singly linked list of children
        Node<T>* child;

        // Singly linked list of hollow roots
        Node<T>* next;

        // a pointer to an extra parent
        Node<T>* ep;

        // if this node is full, this is the key of the item held in this node
        // if this node is hollow, this is the key of the item previously held in this node
        T key;

        // a rank that matches the node's degree
        long long rank;

};

template <typename T>
Node<T>::Node(): item(nullptr), child(nullptr), next(nullptr), ep(nullptr), key(std::numeric_limits<T>::max()), rank(0){}

template <typename T>
Node<T>::Node(Item<T>* e, const T& k): item(e), child(nullptr), next(nullptr), ep(nullptr), key(k), rank(0){}

template <typename  T>
bool Node<T>::operator==(const Node<T>& rhs){
    if (rhs.item == item && rhs.child == child && rhs.next == next && rhs.ep == ep && rhs.key == key && rhs.rank == rank) return true;
    return false;
}

template<typename T>
T& Node<T>::getKey() {
    return key;
}

template<typename T>
Item<T>* Node<T>::getItem(){
    return item;
}

template<typename T>
long long& Node<T>::getRank(){
    return rank;
}

template<typename T>
Node<T>* Node<T>::getChild(){
    return child;
}


template<typename T>
Node<T>* Node<T>::getNext(){
    return next;
}

template<typename T>
Node<T>* Node<T>::getEp(){
    return ep;
}

template<typename T>
void Node<T>::setKey(T& key){
    this->key = key;
}

template<typename T>
void Node<T>::setItem(Item<T>* item){
    this->item = item;
}

template<typename T>
void Node<T>::setRank(long long& rank){
    this->rank = rank;
}

template<typename T>
void Node<T>::setChild(Node<T>* child){
    this->child = child;
}

template<typename T>
void Node<T>::setNext(Node<T>* next){
    this->next = next;
}

template<typename T>
void Node<T>::setEp(Node<T>* ep){
    this->ep = ep;
}

template<typename T>
bool Node<T>::isHollow(){
    return (item == nullptr ? true : false);
}

template <class T>
class HollowHeap{

    public:

        // Constructor
        HollowHeap();

        ~HollowHeap();

        // Return the minimum key in the heap
        T& findMin();

        // Insert a key k into the heap
        Node<T>* insert(const T& k);

        // Decrease the value of the key of a node u to k
        Node<T>* decreaseKey(Node<T>* u, T k);

        // Delete the minimum item in the heap
        void deleteMin();

        // Delete the item in a node n
        void deleteNode(Node<T>* n);

        // Return the max rank in the heap
        long long& getMaxRank();


        // Return true if the heap is empty, false otherwise
        bool isEmpty();
    
    private:

        // link two nodes v and w
        Node<T>* link(Node<T>* v, Node<T>* w);

        // Add a child c to node p
        void addChild(Node<T>* c, Node<T>* p);

        // Meld two nodes g and h
        Node<T>* meld(Node<T>* g, Node<T>* h);

        // The max ran in the heap
        long long maxRank;

        // Pointer to the min node
        Node<T>* min;

        // Number of nodes in the heap
        long long numNodes;

        vector<Node<T>*> toDeleteN;
        vector<Item<T>*> toDeleteI;

};

template <typename T>
HollowHeap<T>::HollowHeap(): maxRank(0), min(nullptr), numNodes(0){}

template <typename T>
HollowHeap<T>::~HollowHeap(){
    for (auto i: toDeleteI){
        delete i;
    }
    for (auto p: toDeleteN){
        delete p;
    }
    
}

// Link two nodes g and h
// Return a pointer to the node with the minimum key
template<typename T>
Node<T>* HollowHeap<T>::link(Node<T>* g, Node<T>* h){

    // If g has a larger key than h, add h as a child to g and return a pointer to h
    if (g->getKey() >= h->getKey()){
        addChild(g,h);
        return h;
    }

    // else add g as a child to h and return a pointer to g
    else{
        addChild(h,g);
        return g;
    }

}

// Meld two subtrees
// Return a pointer to the node with the minimum key
template <typename T>
Node<T>* HollowHeap<T>::meld(Node<T>* g, Node<T>* h){

    if (g==nullptr) {
        return h;
    }

    if (h==nullptr) {
        return g;
    }
    
    return link(g,h);
}

// Insert a key into the heap
// Return inserted node
template <typename T>
Node<T>* HollowHeap<T>::insert(const T& k){

    // Create a new node to hold the key
    Item<T>* e = new Item<T>();
    toDeleteI.push_back(e);
    Node<T>* g = new Node<T>(e,k);
    toDeleteN.push_back(g);
    e->setNode(g);

    // Meld the new node with the min subtree and update the min if applicable
    min = meld(g,min);

    // Increment the number of nodes
    ++numNodes;

    
    // Return inserted node
    return g;
}

// Return the minimum key in the heap
template <typename T>
T& HollowHeap<T>::findMin(){

    return min->getKey();

}

// Decrease the value of the key of a node u to k
// Return the node with the decreased key
template <typename T>
Node<T>* HollowHeap<T>::decreaseKey(Node<T>* u, T k){

    assert(u != nullptr);

    // Assert that the new key is less than the old key
    assert(u->getKey() > k);

    // If the node is hollow, insert a new node with the decreased value
    if (u->getItem() == nullptr){
        Node<T>* v = insert(k);
        return v;
    }

    // if u is the min, decrease the min's key and return
    if (u==min){
        min->setKey(k);
        return min;
    }
    
    // Create new node with the decreased value
    Item<T>* e = u->getItem();
    Node<T>* v = new Node<T>(e,k);
    toDeleteN.push_back(v);
    e->setNode(v);
    u->setItem(nullptr);

    // Update rank of the new node
    long long ranku = u->getRank();
    long long rankR = ranku -2;
    if (ranku > 2) v->setRank(rankR);

    // Link new node with the min and update the min
    Node<T>* tempMin = min;
    min = link(v,min);

    if (tempMin==min){
        // Update child of v and ep of u
        v->setChild(u);
        u->setEp(v);
    }

    return v;

}

// Delete the minimum item in the heap
template <typename T>
void HollowHeap<T>::deleteMin(){
    deleteNode(min);
}

// Delete the item in a node n
template <typename T>
void HollowHeap<T>::deleteNode(Node<T>* n){

    // Assert the node is not null
    assert(n != nullptr);

    // Make the node n hollow
    n->getItem()->setNode(nullptr);
    n->setItem(nullptr);

    // If this is not the min node, perform lazy deletion
    Node<T>* h = min;
    if (h->getItem() != nullptr) {
        --numNodes;
        return;
    }

    maxRank = 0;
    std::map<long long, Node<T>*> A;
    while (h != nullptr){
        Node<T>* w = h->getChild();
        Node<T>* v = h;
        h = h->getNext();

        // Loop through children
        while (w != nullptr){
            Node<T>* u = w;
            w = w->getNext();

            // If u is hollow
            if (u->getItem() == nullptr){

                // If u has one parent
                if (u->getEp() == nullptr){
                    u->setNext(h);
                    h = u;
                }

                // Else if u has two parents
                else{

                    // If v is its second parent, stop looping through children
                    if (u->getEp() == v) w = nullptr;

                    // If v is not the second parent
                    else u->setNext(nullptr);

                    // u loses its second parent
                    u->setEp(nullptr);
                }
            }

            // Else if u is full
            else{

                // Do ranked links
                while (A.find(u->getRank()) != A.end()){
                    u = link(u,A[u->getRank()]);
                    A.erase(u->getRank());
                    long long newRank = u->getRank()+1;
                    u->setRank(newRank);
                }
                A[u->getRank()] = u;
                if (u->getRank() > maxRank){
                    maxRank= u->getRank();
                } 

            }
        }
    }

    // Do unranked links
    for (auto &kv: A){
        if (h == nullptr) h = kv.second;
        else h = link(h,kv.second);
    }

    // Decrement number of nodes
    --numNodes;

    // Update the min node
    min = h;
    if (h != nullptr) min->setNext(nullptr);

}


// Add a child c to node p
template <typename T>
void HollowHeap<T>::addChild(Node<T>* c, Node<T>* p){
   c->setNext(p->getChild());
   p->setChild(c);
}

// Return the mx rank in the heap
template <typename T>
long long& HollowHeap<T>::getMaxRank(){
    return maxRank;
}

// Return true if the heap is empty, false otherwise
template <typename T>
bool HollowHeap<T>::isEmpty(){
    return (numNodes == 0? true : false);
}

vector<int> dijkstra(const Graph& G, long unsigned int src){

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

int main(void){
    ios_base::sync_with_stdio(false); // this stops synchronizing I/O between iostream and stdio, avoiding some overhead
    cin.tie(NULL); // ordinarily cin is tied to cout, meaning cin will flush cout before reading
    cout.tie(NULL);

    int n,m,q,s,u,v,w,t;

    while(cin >> n >> m >> q >> s){
        Graph g(n);
        if (n==0 && m==0 && q==0 && s==0) break;
        while(m--){
            cin >> u >> v >> w;
            g.addEdge(u,v,w);
        }
        vector<int> dist = dijkstra(g,s);
        while(q--){
            cin >> t;
            if (dist[t]==numeric_limits<int>::max() || dist[t] < 0) cout << "Impossible" << endl;
            else cout << dist[t] << endl;   
        }
        cout << endl;
    }
    return 0;
}

