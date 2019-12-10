#include <iostream>
#include <ctime>
#include <chrono>
#include "leftistHeap.h"
#include "WDGraph.h"

const float INF = 10e6;
WDGraph g;
std::vector<VertexNode*> vertices;
std::vector<EdgeNode*> EdgesToNeightbours;
LeftistHeap h;

void readGraph(WDGraph &g);
void createGraphEclipse(WDGraph &g);
void dijkstra(WDGraph g, int src);

int main() {

	readGraph(g);
	// createGraphEclipse(g);

	// g.printGraph();

	auto start = std::chrono::steady_clock::now();
	dijkstra(g, 0);
	auto end2 = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration<double, std::milli>(end2 - start).count()
			<< " ms\n";

	// g.printGraphvertices();

	return 0;
}

void dijkstra(WDGraph g, int src) {

	std::pair<float, int> minElem;
	VertexNode *minElemVertex;
	vertices.clear();
	g.getvertices(vertices);
	g.changeVertexDistance(src, 0);
	for (int i = 0; i < g._nVertex; i++)
		h.insert(std::make_pair(vertices[i]->_dist, vertices[i]->_elem));
	while (!h.isEmpty()) {
		h.deleteMin(minElem);
		minElemVertex = g.getVertex(minElem.second);
		if (minElemVertex->_dist != INF)
			g.visitVertex(minElem.second);
		EdgesToNeightbours.clear();
		g.getNeightbours(minElemVertex->_elem, EdgesToNeightbours);
		for (long unsigned int i = 0; i < EdgesToNeightbours.size(); i++) {
			if (!(g.getVertex(EdgesToNeightbours[i]->_dst)->_visited)
					&& (minElemVertex->_dist + EdgesToNeightbours[i]->_weight
							< g.getVertex(EdgesToNeightbours[i]->_dst)->_dist)) {
				g.changeVertexDistance(EdgesToNeightbours[i]->_dst,
						minElemVertex->_dist + EdgesToNeightbours[i]->_weight);
				g.getVertex(EdgesToNeightbours[i]->_dst)->_parentOnMinPath =
						minElemVertex;h.decreaseKey(g.getVertex(EdgesToNeightbours[i]->_dst)->_elem,
						g.getVertex(EdgesToNeightbours[i]->_dst)->_dist);
			}
			// std::cerr << EdgesToNeightbours.size() - i << " iterations left on the loop\n";
		}
	}
}

void readGraph(WDGraph &g) {
	int src;
	int dst;
	float weight;
	while ((std::cin >> src) && (std::cin >> dst) && (std::cin >> weight)) {
		g.addEdge(src, dst, weight);
	}
}

void createGraphEclipse(WDGraph &g) {
	g.addEdge(0, 4, 101.362);
g.addEdge(0, 7, 62.3941);
g.addEdge(0, 8, 176.601);
g.addEdge(1, 0, 48.7736);
g.addEdge(1, 3, 12.8471);
g.addEdge(2, 0, 41.2987);
g.addEdge(2, 3, 173.611);
g.addEdge(2, 4, 156.678);
g.addEdge(2, 8, 34.2522);
g.addEdge(3, 4, 122.934);
g.addEdge(3, 9, 182.65);
g.addEdge(4, 5, 38.8075);
g.addEdge(4, 6, 77.8586);
g.addEdge(5, 0, 178.964);
g.addEdge(5, 1, 162.324);
g.addEdge(6, 0, 151.737);
g.addEdge(6, 3, 124.569);
g.addEdge(6, 5, 57.2191);
g.addEdge(6, 7, 2.78567);
//g.addEdge(7, 0, 207.942);
g.addEdge(7, 3, 69.091);
g.addEdge(7, 4, 41.7664);
//g.addEdge(7, 6, 204.091);
g.addEdge(8, 3, 222.677);
g.addEdge(8, 4, 153.351);
g.addEdge(8, 9, 10.6995);
g.addEdge(9, 2, 247.934);
//g.addEdge(9, 3, 176.366);
g.addEdge(9, 4, 237.919);
g.addEdge(9, 7, 168.551);
}
