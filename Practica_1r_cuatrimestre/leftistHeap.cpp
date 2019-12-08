#include "leftistHeap.h"

// Node Methods

std::pair<float, int> Node::elem() {
	return _elem;
}
int Node::dist() {
	return _dist;
}
Node* Node::parent() {
	return _parent;
}
Node* Node::left() {
	return _left;
}
Node* Node::right() {
	return _right;
}
void Node::elem(float e) {
	_elem.first = e;
}
void Node::extra(int e) {
	_elem.second = e;
}
void Node::dist(int d) {
	_dist = d;
}
void Node::parent(Node *p) {
	_parent = p;
}
void Node::left(Node *l) {
	_left = l;
}
void Node::right(Node *r) {
	_right = r;
}
Node::Node(std::pair<float, int> e) {
	this->_elem = e;
	this->_dist = 0;
	this->_parent = NULL;
	this->_left = NULL;
	this->_right = NULL;
}

Node::Node(std::pair<float, int> e, int d, Node *parent, Node *l, Node *r) {
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

LeftistHeap::LeftistHeap(Node *newRoot,
		std::unordered_map<int, Node*> *newMap) {
	_root = newRoot;
	_map = newMap;
}

int LeftistHeap::getMin() {
	return _root->elem().first;
}

void LeftistHeap::deleteMin() {
	_map->erase(_root->elem().first);
	Node *aux = _root;
	if (_root->left() != NULL)
		_root->left()->parent(NULL);
	if (_root->right() != NULL)
		_root->right()->parent(NULL);
	_root = mergeHeaps(_root->left(), _root->right());
	delete aux;
}

void LeftistHeap::deleteMin(std::pair<float, int> &minElem) {
	minElem = _root->elem();
	deleteMin();
}

void LeftistHeap::insert(std::pair<int, int> elem) {
	if (_map->find(elem.second) != _map->end()) {
		std::cout << elem.second << " already exists in the heap.\n";
		return;
	}
	Node *newElem = new Node(elem);
	_map->insert(std::make_pair(elem.second, newElem));
	_root = mergeHeaps(_root, newElem);
}

void LeftistHeap::decreaseKey(int elem, float newDist) {
	std::unordered_map<int, Node*>::iterator iter = _map->find(elem);
	if (iter != _map->end()) {
		if (iter->second == _root) {
			_root->elem(newDist);
		} else {
			Node *aux = new Node(
					std::make_pair(newDist, iter->second->elem().second),
					iter->second->dist(), iter->second->parent(),
					iter->second->left(), iter->second->right());
			if ((aux->parent()->left()->elem().second
					== iter->second->elem().second)) {
				aux->parent()->left(NULL);
				swapChildren(aux->parent());
			} else
				aux->parent()->right(NULL);
			aux->parent(NULL);
			_root = mergeHeaps(_root, aux);
			_map->erase(elem);
			_map->insert(std::make_pair(newDist, aux));
		}
	} else {
		std::cout << elem << " not found in the map.\n";
	}
}

void LeftistHeap::merge(LeftistHeap &b) {
	if (this == &b)
		return;     // Can't merge with yourself
	_root = mergeHeaps(_root, b._root);
	b._root = NULL;
}

bool LeftistHeap::isEmpty() {
	return _root == NULL;
}

void LeftistHeap::emptyHeap() {
	clearMem(_root);
	_root = NULL;
	_map->empty();
}

void LeftistHeap::printHeap() {
	LeftistHeap aux;
	aux = *this;
	std::pair<float, int> x;
	while (!aux.isEmpty()) {
		aux.deleteMin(x);
		std::cout << '(' << x.second << ' ' << x.first << ')' << ' ';
	}
	std::cout << '\n';
}

LeftistHeap& LeftistHeap::operator =(LeftistHeap &h) {
	if (this != &h) {
		emptyHeap();
		_root = cloneNode(h._root);
	}
	return *this;
}

std::unordered_map<int, Node*>* LeftistHeap::map() {
	return _map;
}

// Private methods

Node* LeftistHeap::mergeHeaps(Node *heap1, Node *heap2) {
	if (heap1 == NULL)
		return heap2;
	if (heap2 == NULL)
		return heap1;
	if (heap1->elem().first <= heap2->elem().first)
		return MergeRecursive(heap1, heap2); // Ensures heap1 has the smallest root
	return MergeRecursive(heap2, heap1);
}

Node* LeftistHeap::MergeRecursive(Node *heap1, Node *heap2) {
	if (heap1->left() == NULL) {
		heap1->left(heap2);
		heap2->parent(heap1);
	} else {
		heap1->right(mergeHeaps(heap1->right(), heap2));
		heap1->right()->parent(heap1);
		if (heap1->left()->dist() < heap1->right()->dist())
			swapChildren(heap1);
		heap1->dist(heap1->right()->dist() + 1);
	}
	return heap1;
}

void LeftistHeap::swapChildren(Node *parent) {
	Node *aux = parent->right();
	parent->right(parent->left());
	parent->left(aux);
}

void LeftistHeap::clearMem(Node *node) {
	if (node != NULL) {
		clearMem(node->left());
		clearMem(node->right());
		delete node;
	}
}

Node* LeftistHeap::cloneNode(Node *node) {
	if (node == NULL)
		return NULL;
	return new Node(node->elem(), node->dist(), node->parent(),
			cloneNode(node->left()), cloneNode(node->right()));
}
