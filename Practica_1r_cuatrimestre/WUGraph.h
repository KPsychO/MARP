#ifndef _WUGraph_
#define _WUGraph_

#include <iostream>
#include <cstddef>

/*
    Implementation of a Weighted Undirected Graph using Linked lists.
    Each vertex is represented by
*/

class EdgeNode {   // Edges

    public:
        int _src;
        int _dst;
        int _weight;
        EdgeNode* _next;
        EdgeNode(int src, int dst, int weight, EdgeNode* next);

};

class VertexNode {   // Adyacency list (linked list)

    public:
        int _elem;
        bool _visited;
        VertexNode* _next;
        EdgeNode* _edges;
        VertexNode(int elem, VertexNode* next, EdgeNode* edges);

};

class WUGraph {

    public:
        VertexNode* _head;
        int _nVertex;
        void addEdge (int src, int dst, int weight);
        void printGraph();
        WUGraph();

};

#endif