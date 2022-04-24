// Implementation of Node class
#include <limits>
#include "node.h"


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


