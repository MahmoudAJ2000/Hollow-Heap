#pragma once

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
