#pragma once
#include "item.h"

template <typename T> class Item;

template <typename T>
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

        // if this node is full, this is the key of the item held in this node
        // if this node is hollow, this is the key of the item previously held in this node
        T key;

        // a rank that matches the node's degree
        long long rank;

        // Singly linked list of children
        Node<T>* child;

        // Singly linked list of hollow roots
        Node<T>* next;

        // a pointer to an extra parent
        Node<T>* ep;
};