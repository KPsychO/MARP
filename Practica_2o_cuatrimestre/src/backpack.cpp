#include <ctime>
#include <chrono>
#include <cmath>

#include "custom_classes.h"

long unsigned int visited_nodes;

// Generador de datos aletarios para la mochila dado el numeoro de items 
std::vector<MyPair> create_items(int n_items);
// Imprime la solucion
void print_sol(const std::vector<bool> best_sol, std::vector<MyPair> v_w);
// Calculo de la poda para la solucion eficiente
void calc_estimate(std::vector<MyPair> v_w, float maxW, int k, float weight,
		float benefit, float &optimal, float &p, std::vector<bool> &best_sol,
		float &best_benefit);
// Funcion driver de la soluciion eficiente
void backpack_goodpoda(std::vector<MyPair> v_w, float maxW,
		std::vector<bool> &best_sol, float &best_benefit);
// Funcion  recursiva que implementa el backtrack sin podar
void recursive_backpack(std::vector<MyPair> v_w, size_t n, float maxW, Node x,
		std::vector<bool> &best_sol, float &best_benefit, float remainingWeight,
		float remainingValue);
// Funcion driver de la funcion sin poda
void backpack_nopoda(float maxW, std::vector<MyPair> v_w,
		std::vector<bool> &best_sol, float &best_benefit, float totalWeight,
		float totalValue);

// Main -> recibe por parametro el numero de items que debe tener la mochila y el metodo de resolucion
// 1-> eficiente (max aprox. 5000 items en la mochila)
// 2-> sin poda (max aprox. 30 items en la mochila)
int main(int argc, char **argv) {

	srand(time(NULL));

	if (argc != 3) {
		std::cerr << "Wrong number of arguments\n";
		std::cerr
				<< "Correct arguments are: (int) Number of items, (int) Mode (1- goodpoda, 2- nopoda)\n";
		return 1;
	}

	std::cerr << "Generating a backpack with: " << '\n';
	std::cerr << "     " << argv[1] << " items\n";
	std::cerr << "     " << "mode : " << argv[2] << '\n';
	std::cerr << "-----------------------------\n";

	int n_items = std::stoi(argv[1]);
	int mode = std::stoi(argv[2]);
	std::vector<bool> best_sol;
	float best_benefit = 0;
	float totalWeight = 0;
	float totalValue = 0;

	std::vector<MyPair> v_w = create_items(n_items); // generamos el conjunto de datos
	sort(v_w.begin(), v_w.end(), std::greater<MyPair>()); // Ordenamos el conjunto de datos en orden decreciente de valor por unidad de peso (value/weight)

	for (unsigned long int i = 0; i < v_w.size(); i++) {
		totalWeight += v_w[i].weight();
		totalValue += v_w[i].value();
	}
	
    float maxW = totalWeight * 0.45;

	switch (mode) { // seleccionamos el modo
	case 1: {
		visited_nodes = 0;
		best_benefit = 0;
		best_sol.clear();
		best_sol.resize(n_items);

		std::cerr << maxW << '\n';

		auto start = std::chrono::steady_clock::now();
		backpack_goodpoda(v_w, maxW, best_sol, best_benefit);
		auto end = std::chrono::steady_clock::now();

		std::cerr << "\nBuena poda:\n";
		std::cerr
				<< "Tiempo total (ms): 	" << std::chrono::duration<double, std::milli>(end - start).count()
				<< "ms\n";
		std::cerr
				<< "Nodos por ms:		" << visited_nodes
						/ std::chrono::duration<double, std::milli>(end - start).count()
				<< "\n";
		std::cerr << "Tiempo por nodo: 	" << std::chrono::duration<double, std::milli>(end - start).count() / visited_nodes <<
		 " \n";
		std::cerr << "Beneficio maximo:	" << best_benefit << "\n";
		// print_sol(best_sol, v_w); // Descomentar para ver la solucion elegida
		std::cerr << "Nodo visitados:		" << visited_nodes << "\n";
		std::cout
				<< std::chrono::duration<double, std::milli>(end - start).count()
				<< "\n";
		break;
	}

	case 2: {
		visited_nodes = 0;
		best_benefit = 0;
		best_sol.clear();
		best_sol.resize(n_items);

		auto start = std::chrono::steady_clock::now();
		backpack_nopoda(maxW, v_w, best_sol, best_benefit, totalWeight,
				totalValue);
		auto end = std::chrono::steady_clock::now();

		std::cerr << "\nSin poda:\n";
		std::cerr
				<< "Tiempo total (ms): 	" << std::chrono::duration<double, std::milli>(end - start).count()
				<< "ms\n";
		std::cerr
				<< "Nodos por ms:		" << visited_nodes
						/ std::chrono::duration<double, std::milli>(end - start).count()
				<< "\n";
		std::cerr << "Tiempo por nodo: 	" << std::chrono::duration<double, std::milli>(end - start).count() / visited_nodes <<
		 " \n";
		std::cerr << "Beneficio maximo:	" << best_benefit << "\n";
		// print_sol(best_sol, v_w); // Descomentar para ver la solucion elegida
		std::cerr << "Nodo visitados:		" << visited_nodes << "\n";
		std::cout
				<< std::chrono::duration<double, std::milli>(end - start).count()
				<< "\n";
		break;
	}
	default:
		std::cerr << "Mode is not valid (1 or 2 are the available modes)\n";
	}

}

std::vector<MyPair> create_items(int n_items) {

	std::vector<MyPair> ret;
	float f1, f2, f3, f4;

	// std::cerr << "value 		- 	weight\n\n";

	for (int i = 0; i < n_items; i++) {
		f1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		f2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		f3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		f4 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		ret.push_back(
				std::make_pair(f1 * f3 * 20 * n_items, f2 * f4 * 20 * n_items));

		// std::cerr << ret[i].value() << "		-	" << ret[i].weight() << '\n';
	}

	return ret;

}

void print_sol(const std::vector<bool> best_sol, std::vector<MyPair> v_w) {

	for (long unsigned int i = 0; i < best_sol.size(); i++) {
		std::cerr << best_sol[i] << " ";
	}
	std::cerr << "\n";
	for (long unsigned int i = 0; i < best_sol.size(); i++) {
		if (best_sol[i])
			std::cerr << "(" << v_w[i].value() << ", " << v_w[i].weight()
					<< ") ";
	}
	std::cerr << "\n";

}

// Funcion que calcula la cota superior usando el algoritmo voraz que permitia fraccionar los objetos de la mochila
// Dado que el metodo voraz era optimo, no existe solucion sin fraccionar objetos que mejore el valor de la mochila
void calc_estimate(std::vector<MyPair> v_w, float maxW, int k, float weight,
		float benefit, float &optimal, float &p, std::vector<bool> &best_sol,
		float &best_benefit) {

	float h = maxW - weight;
	p = benefit;
	optimal = benefit;

	long unsigned int j = k + 1;

	while (j < best_sol.size() && v_w[j].weight() <= h) {

		h -= v_w[j].weight();
		optimal += v_w[j].value();
		p += v_w[j].value();
		j++;

	}

	if (j < best_sol.size()) {

		optimal += (h / v_w[j].weight()) * v_w[j].value();
		j++;

		while (j < best_sol.size() && h > 0) {

			if (v_w[j].weight() <= h) {

				h -= v_w[j].weight();
				p += v_w[j].value();

			}

			j++;

		}

	}

}

// Backtrack que implementa la solucion trivial
// Tan solo poda cuando el numero de items restantes en la mochila no permite superar la mejor solucion actual
void backpack_goodpoda(std::vector<MyPair> v_w, float maxW,
		std::vector<bool> &best_sol, float &best_benefit) {

	Node x, y;
	x._sol.resize(v_w.size());
	y._sol.resize(v_w.size());

	float p;

	std::priority_queue<Node, std::vector<Node>, std::less<Node>> pqueue;
	y._k = -1;
	y._weight = 0;
	y._benefit = 0;
	calc_estimate(v_w, maxW, y._k, y._weight, y._benefit, y._optimal_benefit,
			best_benefit, best_sol, best_benefit);

	pqueue.push(y);

	while (!pqueue.empty() && (pqueue.top()._optimal_benefit >= best_benefit)) {

		y = pqueue.top();
		pqueue.pop();
		visited_nodes++;
		x._k = y._k + 1;
		x._sol = y._sol;

		if ((y._weight + v_w[x._k].weight()) <= maxW) {
			x._sol[x._k] = 1;
			x._weight = y._weight + v_w[x._k].weight();
			x._benefit = y._benefit + v_w[x._k].value();
			x._optimal_benefit = y._optimal_benefit;

			if (x._k == best_sol.size()) {
				best_sol = x._sol;
				best_benefit = x._benefit;
			} else {
				pqueue.push(x);
			}
		}

		calc_estimate(v_w, maxW, x._k, y._weight, y._benefit,
				x._optimal_benefit, p, best_sol, best_benefit);
		if (x._optimal_benefit >= best_benefit) {
			x._sol[x._k] = 0;
			x._weight = y._weight;
			x._benefit = y._benefit;
			if (x._k == best_sol.size()) {
				best_sol = x._sol;
				best_benefit = x._benefit;
			} else {
				pqueue.push(x);
				best_benefit = std::max(best_benefit, p);
			}
		}
	}
}

void recursive_backpack(std::vector<MyPair> v_w, size_t n, float maxW, Node x,
		std::vector<bool> &best_sol, float &best_benefit, float remainingWeight,
		float remainingValue) {

	visited_nodes++;

	if (x._k == n) {
		if (x._benefit > best_benefit) {
			best_benefit = x._benefit;
			best_sol = x._sol;
		}
		return;
	}

	if (x._weight + v_w[x._k].weight() <= maxW) {
		x._weight += v_w[x._k].weight();
		x._benefit += v_w[x._k].value();
		x._sol[x._k] = 1;
		remainingValue -= v_w[x._k].value();
		remainingWeight -= v_w[x._k].weight();
		x._k++;
		recursive_backpack(v_w, n, maxW, x, best_sol, best_benefit,
				remainingWeight, remainingValue);
		x._k--;
		remainingValue += v_w[x._k].value();
		remainingWeight += v_w[x._k].weight();
		x._weight -= v_w[x._k].weight();
		x._benefit -= v_w[x._k].value();
		x._sol[x._k] = 0;

	}

	if ((x._benefit + remainingValue) > best_benefit) {
		x._k++;
		recursive_backpack(v_w, n, maxW, x, best_sol, best_benefit,
				remainingWeight, remainingValue);
		x._k--;
	}

}

void backpack_nopoda(float maxW, std::vector<MyPair> v_w,
		std::vector<bool> &best_sol, float &best_benefit, float totalWeight,
		float totalValue) {

	Node x;
	x._weight = 0;
	x._benefit = 0;
	x._optimal_benefit = 0;
	x._k = 0;
	x._sol.resize(best_sol.size());

	recursive_backpack(v_w, best_sol.size(), maxW, x, best_sol, best_benefit,
			totalWeight, totalValue);

}
