#include <iostream>
#include "leftistHeap.h"
#include "WDGraph.h"

void dijkstra(WDGraph g, int src) {

		LeftistHeap h;
		VertexNode *vertexs[g._nVertex];
		EdgeNode *EdgesToNeightbours[g._nVertex];
		std::pair<float, int> minElem;
		VertexNode *minElemVertex;
		g.getVertexs(vertexs);

		g.changeVertexDistance(src, 0);

		for (int i = 0; i < g._nVertex; i++)
			h.insert(std::make_pair(vertexs[i]->_dist, vertexs[i]->_elem));

		while (!h.isEmpty()) {

			//		h.printHeap();

			h.deleteMin(minElem);

			//		h.printHeap();

			minElemVertex = g.getVertex(minElem.second);
			if (minElemVertex->_dist != INT_MAX)
				g.visitVertex(minElem.second);
			g.getNeightbours(minElemVertex->_elem, EdgesToNeightbours);
			for (int i = 0; i < g.getNumberOfNeightbours(minElem.second); i++) {
				if (minElemVertex->_dist + EdgesToNeightbours[i]->_weight < g.getVertex(EdgesToNeightbours[i]->_dst)->_dist) {
					g.changeVertexDistance(EdgesToNeightbours[i]->_dst, minElemVertex->_dist + EdgesToNeightbours[i]->_weight);
					g.getVertex(EdgesToNeightbours[i]->_dst)->_parentOnMinPath = minElemVertex;
					h.decreaseKey(g.getVertex(EdgesToNeightbours[i]->_dst)->_elem, g.getVertex(EdgesToNeightbours[i]->_dst)->_dist);
				}
			}

		}

}

int main() {

//			LeftistHeap h;
//
//			h.insert(std::make_pair(19, 1));
//			h.insert(std::make_pair(23, 2));
//			h.insert(std::make_pair(41, 3));
//			h.insert(std::make_pair(34, 4));
//			h.insert(std::make_pair(22, 5));
//			h.insert(std::make_pair(43, 6));
//
//			h.printHeap();
//
//			h.decreaseKey(1, 16);
//
//			h.printHeap();
//
//			h.deleteMin();
//
//			h.printHeap();

	WDGraph g;

	g.addEdge(7, 11, 1);
	g.addEdge(7, 8, 2);
	g.addEdge(5, 11, 3);
	g.addEdge(3, 8, 4);
	g.addEdge(8, 9, 5);
	g.addEdge(3, 10, 6);
	g.addEdge(11, 2, 7);
	g.addEdge(11, 9, 8);
	g.addEdge(11, 10, 9);
	g.addEdge(3, 7, 10);
	g.addEdge(10, 5, 43);
	//	g.printGraph();

	dijkstra(g, 7);

	g.printGraphVertexs();

	return 0;
}
