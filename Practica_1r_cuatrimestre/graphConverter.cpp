#include <iostream>

int main(int argc, char **argv) {

    int src;
	int dst;
	float weight;

    while ((std::cin >> src) && (std::cin >> dst) && (std::cin >> weight))
        std::cout << "g.addEdge(" << src << ", " << dst << ", " << weight << ");\n";

    return 0;

}
