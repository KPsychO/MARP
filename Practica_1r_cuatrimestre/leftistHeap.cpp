#include "leftistHeap.h"

using namespace std;

// Node Methods

Node::Node(const int& e) { }
const int& Node::elem() const { return elem; }
const int& Node::dist() const { return dist; }
const Node& Node::left() const { return left; }
const Node& Node::right() const { return right; }


// LeftistHeap Methods

