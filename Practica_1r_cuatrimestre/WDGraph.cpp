#include "WDGraph.h"

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
        _map = new std::unordered_map<int, VertexNode*>;
    }

    void WUGraph::addEdge (int src, int dst, int weight) {
        if (_head == NULL) {
            EdgeNode* edge1 = new EdgeNode(src, dst, weight, NULL);     // Creamos la arista src -> dst
            VertexNode* aux = new VertexNode(dst, NULL, NULL);          // Creamos el vertice dst
            _head = new VertexNode(src, aux, edge1);                    // Creamos el vertice src y lo asignamos a _head
            _map->insert(std::make_pair(src, _head));
            _map->insert(std::make_pair(dst, aux));
            _nVertex += 2;                                              // Aumentamos el # de vertices
        }
        else {
            EdgeNode* aux = NULL;
            VertexNode* vAux = NULL;
            std::unordered_map<int, VertexNode*>::iterator iter = _map->find(src);
            if(iter != _map->end()){
                aux = iter->second->_edges;
                iter->second->_edges = new EdgeNode(src, dst, weight, aux);
            }
            else {
                EdgeNode* eAux = new EdgeNode(src, dst, weight, NULL);
                vAux = _head;
                _head = new VertexNode(src, vAux, eAux);
                _map->insert(std::make_pair(src, _head));
                _nVertex++;
            }
            iter = _map->find(dst);
            if (iter == _map->end()){
                vAux = _head;
                _head = new VertexNode(dst, vAux, NULL);
                _map->insert(std::make_pair(dst, _head));
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
