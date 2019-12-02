#include "leftistHeap.h"

// Node Methods

    int Node::elem() { return _elem; }
    int Node::dist() { return _dist; }
    Node* Node::parent() { return _parent; }
    Node* Node::left() { return _left; }
    Node* Node::right() { return _right; }
    void Node::elem(int e) { _elem = e; }
    void Node::dist(int d) { _dist = d; }
    void Node::parent(Node* p) { _parent = p; }
    void Node::left(Node* l) { _left = l; }
    void Node::right(Node* r) { _right = r; }
    Node::Node(const int &e) {
        this->_elem = e;
        this->_dist = 0;
        this->_parent = NULL;
        this->_left = NULL;
        this->_right = NULL;

    }

    Node::Node(int e, int d, Node* parent, Node* l, Node* r){
        this->_elem = e;
        this->_dist = d;
        this->_parent = parent;
        this->_left = l;
        this->_right = r;
    }


// LeftistHeap Methods

    // Public methods

    LeftistHeap::LeftistHeap() {
        _root = NULL;
        _map = new std::unordered_map<int, Node*>;
    }

    LeftistHeap::LeftistHeap(Node* newRoot, std::unordered_map<int, Node*>* newMap){
    	_root = newRoot;
    	_map = newMap;
    }

    int LeftistHeap::getMin(){
        return _root->elem();
    }

    void LeftistHeap::deleteMin(){
        _map->erase(_root->elem());
        Node *aux = _root;
        _root = mergeHeaps(_root->left(), _root->right());
        delete aux;
    }

    void LeftistHeap::deleteMin(int &minElem){
        minElem = _root->elem();
        deleteMin();
    }

    void LeftistHeap::insert(int elem){
        if (_map->find(elem) != _map->end()) {
            std::cout << elem << " already exists in the heap.\n";
            return;
        }
        Node* newElem = new Node(elem);
        _map->insert(std::make_pair(elem, newElem));
        _root = mergeHeaps(_root, newElem);
    }

    void LeftistHeap::decreaseKey(int oldKey, int newKey){
        if (oldKey < newKey) {
            std::cout << "LeftistHeap::decreaseKey(int oldKey, int newKey): Received a newKey bigger than the original key.\n";
            return;
        }
        std::unordered_map<int, Node*>::iterator iter = _map->find(oldKey);
        if (iter != _map->end()){
            Node* aux = new Node(newKey, iter->second->dist(), iter->second->parent(), iter->second->left(), iter->second->right());
            if(aux->parent()->left()->elem() == oldKey)
            	aux->parent()->left(NULL);
            else
            	aux->parent()->right(NULL);
            aux->parent(NULL);
            aux->elem(newKey);
            _root = mergeHeaps(_root, aux);
            _map->erase(oldKey);
            _map->insert(std::make_pair(newKey, aux));
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
        _map->empty();
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
            _root = cloneNode(h._root);
        }
        return *this;
    }

    std::unordered_map<int, Node*>* LeftistHeap::map() { return _map; }

    // Private methods

    Node* LeftistHeap::mergeHeaps(Node *heap1, Node *heap2){
        if (heap1 == NULL) return heap2;
        if (heap2 == NULL) return heap1;
        if(heap1->elem() < heap2->elem()) return MergeRecursive(heap1, heap2); // Ensures heap1 has the smallest root
        return MergeRecursive(heap2, heap1);
    }

    Node* LeftistHeap::MergeRecursive(Node *heap1, Node *heap2){
        if(heap1->left() == NULL) {
        	heap1->left(heap2);
        	heap2->parent(heap1);
        }
        else {
            heap1->right(mergeHeaps(heap1->right(), heap2));
            heap1->right()->parent(heap1);
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
        return new Node (node->elem(), node->dist(), node->parent(), cloneNode(node->left()), cloneNode(node->right()));
    }