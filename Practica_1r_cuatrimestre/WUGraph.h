#ifndef _WUGraph_
#define _WUGraph_

#include <iostream>
#include <cstddef>
#include <unordered_map>

/*
    Implementation of a Weighted Undirected Graph using Linked lists.
    Each vertex is represented by VertexNode:
        _elem       contains the value of the given node
        _visited    controls if the visited has been visited by any algorithm
        _next       pointer to the next VertexNode in the graph
        _edges      pointer to the first EdgeNode of the Vertex

    Each edge is represented by EdgeNode:
        _src        contains the value from the vertex wich the edge comes out
        _dst        contains the value from the vertex wich the edge goes to
        _weight     contains the cost of traveling trought the given edge
        _next       pointer to the next edge of the given VertexNode

    The complete graph is represented by WUGraph:
        _head       pointer to the first VertexNode in the graph
*/

class EdgeNode {   // Edges

    public:
        int _src;
        int _dst;
        int _weight;
        EdgeNode* _next;
        EdgeNode(int src, int dst, int weight, EdgeNode* next);     // Constructor 

};

class VertexNode {   // Adyacency list (linked list)

    public:
        int _elem;
        bool _visited;
        VertexNode* _next;
        EdgeNode* _edges;
        VertexNode(int elem, VertexNode* next, EdgeNode* edges);    // Constructor

};

class WUGraph {

    public:
        VertexNode* _head;
        int _nVertex;
        std::unordered_map<int, VertexNode*>* _map;
        void addEdge (int src, int dst, int weight);    // Adds an EdgeNode from src to dst with the given weight
        void printGraph();                              // Prints the adyacency list for the graph
        WUGraph();                                      // Constructor

};

#endif