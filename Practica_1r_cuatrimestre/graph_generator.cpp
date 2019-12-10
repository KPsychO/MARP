#include <cstdlib>
#include <ctime>
#include <iostream>

void createGraph(int MAX_VERTICES, int MAX_WEIGHT, float EDGE_CHANCE){

	float r;
    float f;

    for (int row = 0; row < MAX_VERTICES; row++){
		for (int col = 0; col < MAX_VERTICES; col++){

			if (row != col){
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

				if (r <= EDGE_CHANCE){
					f = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//				    g.addEdge(row, col, r * MAX_WEIGHT);
					std::cout << row << ' ' << col << ' ' << f*MAX_WEIGHT << '\n';
                }

			}

		}
	}

}

int main(int argc, char **argv) {

    if (argc != 4){
        std::cerr << "Wrong # of arguments\n";
        std::cerr << "Correct arguments are: (int) MAX_VERTICES, (int) MAX_WEIGHT, (float) EDGE_CHANCE\n";
        return 1;
    }

    std::cerr << "Generating a graph with: " << '\n';
    std::cerr << argv[1] << " MAX_VERTICES\n";
    std::cerr << argv[2] << " MAX_WEIGHT\n";
    std::cerr << argv[3] << " EDGE_CHANCE\n";

    createGraph(std::stoi(argv[1]), std::stoi(argv[2]), std::stod(argv[3]));

    return 0;

}
