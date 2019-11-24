#include "WUGraph.h"

// EdgeNode methods

    EdgeNode::EdgeNode (int src, int dst, int weight, EdgeNode* next){
        _src = src;
        _dst = dst;
        _weight = weight;
        _next = next;
    }

// VertexNode methods

    VertexNode::VertexNode(int elem, VertexNode* next, EdgeNode* edges){
        _elem = elem;
        _visited = 0;
        _next = next;
        _edges = edges;
    }

// WUGraph methods

    WUGraph::WUGraph() {
        _head = NULL;
        _nVertex = 0;
    }

    void WUGraph::addEdge (int src, int dst, int weight) {
        if (_head == NULL) {
            EdgeNode* edge1 = new EdgeNode(src, dst, weight, NULL);
            EdgeNode* edge2 = new EdgeNode(dst, src, weight,  NULL);
            VertexNode* aux = new VertexNode(dst, NULL, edge2);;
            _head = new VertexNode(src, aux, edge1);
            _nVertex += 2;
        }
        else {
            VertexNode* iter = _head;
            EdgeNode* aux = NULL;
            bool bsrc = 0;
            bool bdst = 0;
            while (iter && (!bsrc || !bdst)){
                if (iter->_elem == src){
                    aux = iter->_edges;
                    iter->_edges = new EdgeNode(src, dst, weight, aux);
                    bsrc = 1;
                }
                if(iter->_elem == dst){
                    aux = iter->_edges;
                    iter->_edges = new EdgeNode(dst, src, weight, aux);
                    bdst = 1;
                }
                iter = iter->_next;
            }
            if (!bsrc){
                VertexNode* aux = _head->_next;
                EdgeNode* edges = new EdgeNode(src, dst, weight, NULL);
                _head->_next = new VertexNode(src, aux, edges);
                _nVertex++;
            }
            if (!bdst){
                VertexNode* aux = _head->_next;
                EdgeNode* edges = new EdgeNode(dst, src, weight, NULL);
                _head->_next = new VertexNode(dst, aux, edges);
                _nVertex++;
            }
        }
    }

    void WUGraph::printGraph() {
        VertexNode* vertex = _head;
        for(int i = 0; i < _nVertex; i++){
            std::cout << "Adyacency list of: " << vertex->_elem << '\n';
            EdgeNode* edge = vertex->_edges;
            while(edge){
                std::cout << " -> " << edge->_dst << " (" << edge->_weight << ')';
                edge = edge->_next;
            }
            std::cout << '\n';
            vertex = vertex->_next;
        }
    }
