#include <bits/stdc++.h>
#include "item.cpp"
#include "node.cpp"
#include "hollowHeap.cpp"

using namespace std;



int main(void){

    Node<int>* n;
    set<Node<int>*> nodes;
    int min;

    HollowHeap<int> HH;

    cout << endl;

    // test isEmpty
    cout << "#test isEmpty(): " << endl;
    assert(HH.isEmpty());
    cout << "Heap is empty" << endl;
    cout << endl;

    // test insert and findMin
    cout << "#test insert() and findMin(): " << endl;
    cout << "insert(3)" << endl;
    n = HH.insert(3);
    nodes.insert(n);
    cout << "findMin()" << endl;
    min = HH.findMin();
    assert(min == 3);
    cout << "min is now: "<< min << endl;
    cout << endl;

    // test deleteMin
    cout << "#test deleteMin(): " << endl;
    cout << "insert(8)" << endl;
    n = HH.insert(8);
    nodes.insert(n);
    cout << "deleteMin()" << endl;
    HH.deleteMin();
    nodes.erase(nodes.begin());
    cout << "findMin()" << endl;
    min = HH.findMin();
    assert(min==8);
    cout << "min is now: "<< min << endl;
    cout << endl;

    // test deleteNode
    cout << "#test deleteNode(): " << endl;
    cout << "insert(12)" << endl;
    n = HH.insert(12);
    nodes.insert(n);
    cout << "insert(4)" << endl;
    Node<int>* m = HH.insert(4);
    nodes.insert(m);
    cout << "insert(6)" << endl;
    Node<int>* s = HH.insert(6);
    nodes.insert(s);
    cout << "deleteNode(6)" << endl;
    HH.deleteNode(s);
    cout << "deleteNode(4)" << endl;
    HH.deleteNode(m);
    cout << "findMin()" << endl;
    min = HH.findMin();
    assert(min == 7);
    cout << "min is now: "<< min << endl;
    cout << endl;

    // test decreaseKey
    cout << "#test decreaseKey(): " << endl;
    cout << "insert(7)" << endl;
    n = HH.insert(7);
    nodes.insert(n);
    cout << "insert(11)" << endl;
    n = HH.insert(11);
    nodes.insert(n);
    cout << "decreaseKey(11,0)" << endl;
    HH.decreaseKey(n,0);
    cout << "findMin()" << endl;
    min = HH.findMin();
    assert(min==0);
    cout << "min is now: "<< min << endl;
    cout << endl;

    

    return 0;
}