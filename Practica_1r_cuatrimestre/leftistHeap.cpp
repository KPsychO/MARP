#include "leftistHeap.h"

// Node Methods

    int Node::elem() { return _elem; }
    int Node::dist() { return _dist; }
    Node* Node::left() { return _left; }
    Node* Node::right() { return _right; }
    void Node::elem(int e) { _elem = e; }
    void Node::dist(int d) { _dist = d; }
    void Node::left(Node* l) { _left = l; }
    void Node::right(Node* r) { _right = r; }


// LeftistHeap Methods

    // Public methods

    LeftistHeap::LeftistHeap(){
        _root = NULL;
        _map.clear();
    }

    int LeftistHeap::getMin(){
        return _root->elem();
    }

    void LeftistHeap::deleteMin(){
        _map.erase(_root->elem());
        Node *aux = _root;
        _root = mergeHeaps(_root->left(), _root->right());
        delete aux;
    }

    void LeftistHeap::deleteMin(int &minElem){
        minElem = _root->elem();
        deleteMin();
    }

    void LeftistHeap::insert(int elem){
        if (_map.find(elem) != _map.end()) {
            std::cout << elem << " already exists in the heap.\n";
            return;
        }
        Node* newElem = new Node(elem);
        _map[elem] = newElem;
        _root = mergeHeaps(_root, newElem);
    }

    void LeftistHeap::decreaseKey(int oldKey, int newKey){
        std::unordered_map<int, Node*>::iterator iter = _map.find(oldKey);
        if (iter != _map.end()){
            Node* aux = new Node(iter->second->elem(), iter->second->dist(), iter->second->left(), iter->second->right());
            aux->elem(newKey);
            // delte the pointer IN THE FUCKING HEAP
            _map.erase(oldKey);
            _map[newKey] = aux;
            _root = mergeHeaps(_root, aux);
        }
        else {
            std::cout << oldKey << " not found in the map.\n";
        }
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
        _map.empty();
    }

    void LeftistHeap::printHeap(){
        LeftistHeap aux;
        aux = *this;
        int x;
        while(!aux.isEmpty()) {
            aux.deleteMin(x);
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }

    LeftistHeap& LeftistHeap::operator =(LeftistHeap &h){
        if (this != &h){
            emptyHeap();
            _root = cloneNode(h.root());
        }
        return *this;
    }

    Node* LeftistHeap::root() { return _root; }

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

    Node* LeftistHeap::cloneNode(Node* node){
        if (node == NULL) return NULL;
        return new Node (node->elem(), node->dist(), cloneNode(node->left()), cloneNode(node->right()));
    }
