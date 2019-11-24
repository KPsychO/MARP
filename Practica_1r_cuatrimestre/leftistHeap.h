/*
    FUNCTION:       COMPLEXITY:
    - getMin()       - O(1)
    - deleteMin()    - O(log N)
    - insert()       - O(log N)
    - merge()        - O(log N)

    Node Info:
        - element
        - distance
        - left child
        - right child

    Operations:
        - merge() is the main operation, called by deleteMin(), getMin() an d insert()
        - deleteMin() removes the root of the tree and calls merge with both the left and right sons
        - getMin() returns the value of the pointer to the root
        - insert() creates a leftist heap with a single key and calls merge with the original and this new tree

*/

#ifndef _LeftistHeap_
#define _LeftistHeap_

#include <cstddef>

class Node{

    public:
        int elem();             // Returns the element from the node
        int dist();             // Returns the distance from the node
        Node* left();           // Returns the left son of the node
        Node* right();          // Returns the right son of the node
        void dist(int d);       // Sets the new value for _dist to the given int
        void left(Node* l);     // Sets the new value for the left child
        void right(Node* r);    // Sets the new value for the right child
        Node(const int &e){     // Constructor
            this->_elem = e;
            this->_dist = 0;
            this->_left = NULL;
            this->_right = NULL;
        }
    
    private:
        int _elem;
        int _dist;
        Node *_left;
        Node *_right;

};

class LeftistHeap{

    public:
        LeftistHeap();                      // Constructor
        LeftistHeap(LeftistHeap &heap);     // Constructor by copy
        int getMin();                       // Returns the smallest element in the heap (root)
        void deleteMin();                   // Removes the smallest element in the heap
        void deleteMin(int &minElem);       // Removes the smallest element in the heap and returns it, used instead getMin() followed by deleteMin()
        void insert(int &elem);             // Inserts the given element into the heap
        void merge(LeftistHeap &b);         // Merges the existing heap with the given one
        bool isEmpty();                     // Tests if the heap is empty
        void emptyHeap();                   // Empties the heap

    private:
        Node *_root;
        Node* mergeHeaps(Node *heap1, Node *heap2);         // Merges both heaps, returning the root to the resulting heap
        Node* MergeRecursive(Node *heap1, Node *heap2);     // Called by mergeHeaps() recursively
        void swapChildren(Node *parent);                    // Swaps the right and left childs of the given node
        void clearMem(Node *node);                          // Clears the dinamically allocated memory of the heap

};

#endif