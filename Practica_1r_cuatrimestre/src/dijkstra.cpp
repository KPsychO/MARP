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
void createGraph(int N_VERTICES, int MAX_WEIGHT, float EDGE_CHANCE);
void dijkstra(WDGraph g, int src);

int main(int argc, char **argv) {

    srand(time(NULL));  
    if (argc != 4){
        std::cerr << "Wrong # of arguments\n";
        std::cerr << "Correct arguments are: (int) N_VERTICES, (int) MAX_WEIGHT, (float) EDGE_CHANCE\n";
        return 1;
    }
    std::cerr << "Generating a graph with: " << '\n';
    std::cerr << "     " << argv[1] << " N_VERTICES\n";
    std::cerr << "     " << argv[2] << " MAX_WEIGHT\n";
    std::cerr << "     " << argv[3] << " EDGE_CHANCE\n";
	std::cerr << "-------------------------\n";
	// readGraph(g);		// Descomentar para leer el grafo (./dijkstra < inputFile)
    createGraph(std::stoi(argv[1]), std::stoi(argv[2]), std::stod(argv[3]));	// Comentar si se desea leer el grafo en lugar de generarlo
	// g.printGraph();		// Descomentar para imprimir las listas de adyacencia del grafo generado o leido
	auto start = std::chrono::steady_clock::now();
	dijkstra(g, 0);
	auto end = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration<double, std::milli>(end - start).count()	<< "\n";
	// g.printGraphvertices();	// Descomentar para imprimir los datos de todos los vertices tras la ejecucion del algoritmo
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
				&& (minElemVertex->_dist + EdgesToNeightbours[i]->_weight < g.getVertex(EdgesToNeightbours[i]->_dst)->_dist)) {
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
	while ((std::cin >> src) && (std::cin >> dst) && (std::cin >> weight)) {
		g.addEdge(src, dst, weight);
	}
}

void createGraph(int N_VERTICES, int MAX_WEIGHT, float EDGE_CHANCE){

	float r;
    float f;

    for (int row = 0; row < N_VERTICES; row++){
		for (int col = 0; col < N_VERTICES; col++){
			if (row != col){
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (r <= EDGE_CHANCE){
					f = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    g.addEdge(row, col, f*MAX_WEIGHT);
                }
			}
		}
	}
}