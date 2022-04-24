// Implementation of Item class
#include "item.h"

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
