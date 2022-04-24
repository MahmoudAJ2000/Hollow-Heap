// Implementation of HollowHeap class
#include <assert.h>
#include <map>
#include <list>
#include <iostream>
#include <limits>
#include "hollowHeap.h"

using namespace std;

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