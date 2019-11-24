#include "leftistHeap.h"

using namespace std;

// Node Methods

    int Node::elem() { return _elem; }
    int Node::dist() { return _dist; }
    Node* Node::left() { return _left; }
    Node* Node::right() { return _right; }
    void Node::dist(int d) { _dist = d; }
    void Node::left(Node* l) { _left = l; }
    void Node::right(Node* r) { _right = r; }


// LeftistHeap Methods
    
    // Public methods

    LeftistHeap::LeftistHeap(){
        _root = NULL;
    }

    LeftistHeap::LeftistHeap(LeftistHeap &heap){
        *this = heap;
    }
    
    int LeftistHeap::getMin(){
        return _root->elem();
    }
    
    void LeftistHeap::deleteMin(){
        Node *aux = _root;
        _root = mergeHeaps(_root->left(), _root->right());
        delete aux;
    }
    
    void LeftistHeap::deleteMin(int &minElem){
        minElem = _root->elem();
        deleteMin();
    }
    
    void LeftistHeap::insert(int &elem){
        _root = mergeHeaps(_root, new Node(elem));
    }
    
    void LeftistHeap::merge(LeftistHeap &b){
        if (this == &b) return;     // Can't merge with yourself
        _root = mergeHeaps(_root, b._root);
        b._root = NULL;
    }
    
    bool LeftistHeap::isEmpty(){
        return _root == NULL;
    }
    
    void LeftistHeap::emptyHeap(){
        clearMem(_root);
        _root = NULL;
    }

    // Private methods

    Node* LeftistHeap::mergeHeaps(Node *heap1, Node *heap2){
        if (heap1 == NULL) return heap2;
        if (heap2 == NULL) return heap1;
        if(heap1->elem() < heap2->elem()) return MergeRecursive(heap1, heap2); // Ensures heap1 has the sammlest root
        return MergeRecursive(heap2, heap1);
    }
    
    Node* LeftistHeap::MergeRecursive(Node *heap1, Node *heap2){
        if(heap1->left() == NULL) heap1->left(heap2);
        else {
            heap1->right(mergeHeaps(heap1->right(), heap2));
            if (heap1->left()->dist() < heap1->right()->dist()) swapChildren(heap1);
            heap1->dist(heap1->right()->dist() + 1);
        }
        return heap1;
    }
    
    void LeftistHeap::swapChildren(Node *parent){
        Node *aux = parent->right();
        parent->right(parent->left());
        parent->left(aux);
    }
    
    void LeftistHeap::clearMem(Node *node) {
        if (node != NULL){
            clearMem(node->left());
            clearMem(node->right());
            delete node;
        }
    }