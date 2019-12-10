#include <iostream>

#include "leftistHeap.h"
#include "WDGraph.h"

const float INF = 10e6;
std::vector<VertexNode*> vertices;
std::vector<EdgeNode*> EdgesToNeightbours;
// bool matrix[MAX_VERTICES][MAX_VERTICES] = {0};

void readGraph(WDGraph &g);
void dijkstra(WDGraph g, int src);

int main() {

	WDGraph g;

    readGraph(g);

	srand (time(NULL));
	// g.printGraph();
	dijkstra(g, 0);
	 g.printGraphvertices();

	return 0;
}

void dijkstra(WDGraph g, int src) {
	LeftistHeap h;
	std::pair<float, int> minElem;
	VertexNode *minElemVertex;
	g.getvertices(vertices);
	g.changeVertexDistance(src, 0);
	for (int i = 0; i < g._nVertex; i++)
		h.insert(std::make_pair(vertices[i]->_dist, vertices[i]->_elem));
	while (!h.isEmpty()) {
		h.deleteMin(minElem);
		minElemVertex = g.getVertex(minElem.second);
			if (minElemVertex->_dist != INF)
				g.visitVertex(minElem.second);
			g.getNeightbours(minElemVertex->_elem, EdgesToNeightbours);
			for (int i = 0; i < g.getNumberOfNeightbours(minElem.second); i++) {
				if ((g.getVertex(EdgesToNeightbours[i]->_dst)->_visited == 0) && (minElemVertex->_dist + EdgesToNeightbours[i]->_weight < g.getVertex(EdgesToNeightbours[i]->_dst)->_dist)) {
					g.changeVertexDistance(EdgesToNeightbours[i]->_dst, minElemVertex->_dist + EdgesToNeightbours[i]->_weight);
					g.getVertex(EdgesToNeightbours[i]->_dst)->_parentOnMinPath = minElemVertex;
					h.decreaseKey(g.getVertex(EdgesToNeightbours[i]->_dst)->_elem, g.getVertex(EdgesToNeightbours[i]->_dst)->_dist);
				}
			}
	}
}

void readGraph(WDGraph &g) {
    int src;
    int dst;
    float weight;
    while((std::cin >> src) && (std::cin >> dst) && (std::cin >> weight)) {
        g.addEdge(src, dst, weight);
    }
}
