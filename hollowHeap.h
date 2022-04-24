#pragma once
#include <vector>
#include <map>
#include "node.h"

template <typename T>
class HollowHeap{

    public:

        // Constructor
        HollowHeap();

        // Destructor
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

        // vectors storing pointers to free
        std::vector<Node<T>*> toDeleteN;
        std::vector<Item<T>*> toDeleteI;

};
