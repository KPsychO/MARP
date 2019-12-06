#include "WDGraph.h"

#define INF INT_MAX

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
        _dist = INF;
        _nodesPointed = 0;
        _visited = 0;
        _next = next;
        _edges = edges;
    }

// WDGraph methods

    WDGraph::WDGraph() {
        _head = NULL;
        _nVertex = 0;
        _map = new std::unordered_map<int, VertexNode*>;
    }

    void WDGraph::addEdge (int src, int dst, int weight) {
        if (_head == NULL) {
            EdgeNode* edge1 = new EdgeNode(src, dst, weight, NULL);     // Creamos la arista src -> dst
            VertexNode* aux = new VertexNode(dst, NULL, NULL);          // Creamos el vertice dst
            _head = new VertexNode(src, aux, edge1);                    // Creamos el vertice src y lo asignamos a _head
            _head->_nodesPointed++;
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
                iter->second->_nodesPointed++;
            }
            else {
                EdgeNode* eAux = new EdgeNode(src, dst, weight, NULL);
                vAux = _head;
                _head = new VertexNode(src, vAux, eAux);
                _head->_nodesPointed++;
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

    void WDGraph::printGraph() {
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

    void WDGraph::printGraphVertexs() {
        VertexNode* vertex = _head;
        for(int i = 0; i < _nVertex; i++){
            std::cout << "Vertex: " << vertex->_elem << '\n';
            std::cout << "   # of pointed nodes: " << vertex->_nodesPointed << '\n';
            std::cout << "   visited: " << ( vertex->_visited ? "True\n" : "False\n");
            std::cout << "   distance: " << vertex->_dist << '\n';
            std::cout << '\n';
            vertex = vertex->_next;
        }
    }

    VertexNode* WDGraph::getVertexs() {
        VertexNode* vertex = _head;
        VertexNode* ret[_nVertex];
        for(int i = 0; i < _nVertex; i++){
            ret[i] = vertex;
            vertex = vertex->_next;
        }
        return ret;
    }

    void WDGraph::changeVertexDistance(int e, int newDist){
        std::unordered_map<int, VertexNode*>::iterator iter = _map->find(src);
        if(iter != _map->end()){
            iter->second->_dist = newDist;
        }
        else {
            std::cout << e << "Is not currently in the graph.\n";
        }
    }

    void WDGraph::visitVertex(int e){
        std::unordered_map<int, VertexNode*>::iterator iter = _map->find(src);
        if(iter != _map->end()){
            iter->second->_visited = 1;
        }
        else {
            std::cout << e << "Is not currently in the graph.\n";
        }
    }

    std::pait<int, float>* WDGraph::getNeightbours(int e){
        std::unordered_map<int, VertexNode*>::iterator iter = _map->find(src);
        std::pait<int, float> ret[iter->second->_nodesPointed];
        EdgeNode* aux;
        if(iter != _map->end()){
            for(int i = 0; i < iter->second->_nodesPointed; i++){
                aux = iter->second->_edges;
                ret[i] = std::make_pair(aux->_dst, aux->_weight);
            }
        }
        else {
            std::cout << e << "Is not currently in the graph.\n";
        }
        return ret;
    }

    int WDGraph::getNumberOfNeightbours(int e){        
        std::unordered_map<int, VertexNode*>::iterator iter = _map->find(src);
        if(iter != _map->end()){
            return iter->second->_nodesPointed;
        }
        else {
            std::cout << e << "Is not currently in the graph.\n";
        }
    }