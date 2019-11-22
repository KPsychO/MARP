/*
    FUNCTION:       COMPLEXITY:
    - getMin()       - O(1)
    - deleteMin()    - O(log N)
    - insert()       - O(log N)
    - merge()        - O(log N)

    Node Info:
        - element
        - distance
        - left son
        - right son

    Operations:
        - merge() is the main operation, called by deleteMin(), getMin() an d insert()
        - deleteMin() removes the root of the tree and calls merge with both the left and right sons
        - getMin() returns the value of the pointer to the root
        - insert() creates a leftist heap with a single key and calls merge with the original and this new tree

*/

#ifndef _LeftistHeap_
#define _LeftistHeap_

class Node{

    public:
        const int& elem() const;      // Returns the element from the node
        const int& dist() const;      // Returns the distance from the node
        const Node& left() const;     // Returns the left son of the node
        const Node& right() const;    // Returns the right son of the node
        // Constructor
        Node(const int &e, const int d = 0, const Node *l = NULL, const Node *r = NULL){
            this->elem = e;
            this->dist = d;
            this->left = l;
            this->right = r;
        }
    
    private:
        int elem;
        int dist;
        Node * left;
        Node * right;

}



class LeftistHeap{

    public:
        LeftistHeap();                      // Constructor
        LeftistHeap(LeftistHeap &heap);     // Constructor by copy
        int getMin();                       // Returns the smallest element in the heap (root)
        void deleteMin();                   //  Removes the smallest element in the heap
        // void deleteMin(int &minElem);       // Removes the smallest element in the heap and returns it
        void insert(int &elem);             // Inserts the given element into the heap
        void merge(LeftistHeap &b);         // Merges the existing heap with the given one
        bool isEmpty();                     // Tests if the heap is empty
        void emptyHeap();                   // Empties the heap
        // operator &

    private:
        Node *root;
        Node *mergeHeaps(Node *heap1, Node *heap2);         // Merges both heaps, returning the root to the resulting heap
        Node *MergeRecursive(Node *heap1, Node *heap2);     // Called by mergeHeaps() recursively
        void swapChildren(Node *parent);
        // reclaimMemory
        // clone

}

#endif