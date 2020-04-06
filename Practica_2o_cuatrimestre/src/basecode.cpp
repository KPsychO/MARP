#include <queue>        // std::priority_queue
#include <vector>       // std::vector
#include <algorithm>    // std::max
#include <iostream>     // std::cout

class Node {

    public:
        std::vector<bool> _sol;
        int _k;
        float _weight, _benefit, _optimal_benefit;
        
        friend bool operator<(const Node &n, const Node &m) { return (n._optimal_benefit < m._optimal_benefit); }
        friend bool operator>(const Node &n, const Node &m) { return (m._optimal_benefit < n._optimal_benefit); }
        friend bool operator<=(const Node &n, const Node &m) { return !(n._optimal_benefit > m._optimal_benefit); }
        friend bool operator>=(const Node &n, const Node &m) { return !(n._optimal_benefit < m._optimal_benefit); }

};

std::vector<bool> best_sol;
float best_benefit;

void print_sol() {

	for (int i = 0; i < best_sol.size(); i++){

		std::cout << best_sol[i] << " ";

	}

	std::cout << "\n";

}

void calc_estimate (std::vector<float> weights, std::vector<float> values, float maxW, int k, float weight, float benefit, float &optimal, float &p) {

    float h = maxW - weight;
    p = benefit;
    optimal = benefit;

    int j = k+1;

    while (j < best_sol.size() && weights[j] <= h) {

        h -= weights[j];
        optimal += values[j];
        p += values[j];
        j++;

    }

    if (j < best_sol.size()){

        optimal += (h/weights[j]) * values[j];
        j++;

        while (j < best_sol.size() && h > 0) {

            if (weights[j] <= h){

                h -= weights[j];
                p += values[j];

            }

            j++;

        }

    }
    
}

void backpack (std::vector<float> weights, std::vector<float> values, float maxW) {

    // FALTA PUTO DESMARCAR LA SOLUCION
    // sino, siempre pilla los primeros
    // o... eso pensaba el Diego del pasado

    best_benefit = 0;
    best_sol.clear();
    best_sol.resize(values.size());

    Node x, y;
    x._sol.resize(values.size());
    y._sol.resize(values.size());

    float p;

    std::priority_queue<Node, std::vector<Node>, std::less<Node>> pqueue;
    y._k = -1;
    y._weight = 0;
    y._benefit = 0;
    calc_estimate(weights, values, maxW, y._k, y._weight, y._benefit, y._optimal_benefit, best_benefit);

    pqueue.push(y);

    while(!pqueue.empty() && (pqueue.top()._optimal_benefit >= best_benefit)){

        y = pqueue.top();
        pqueue.pop();
        x._k = y._k+1;
        x._sol = y._sol;

        if ((y._weight + weights[x._k]) <= maxW) {
            x._sol[x._k] = 1;
            x._weight = y._weight + weights[x._k];
            x._benefit = y._benefit + values[x._k];
            x._optimal_benefit = y._optimal_benefit;

            if (x._k == best_sol.size()) {
                best_sol = x._sol;
                best_benefit = x._benefit;
            }
            else {
                pqueue.push(x);
            }
        }

        calc_estimate(weights, values, maxW, x._k, y._weight, y._benefit, x._optimal_benefit, p);
        if(x._optimal_benefit >= best_benefit){
            x._sol[x._k] = 0;
            x._weight = y._weight;
            x._benefit = y._benefit;
            if (x._k == best_sol.size()) {
                best_sol = x._sol;
                best_benefit = x._benefit;
            }
            else {
                pqueue.push(x);
                best_benefit = std::max(best_benefit, p);
            }
        }
    }
}

int main () {

    std::vector<float> weights = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    std::vector<float> values = {234, 563, 123, 454, 23, 312, 634, 74, 4000021};
    float maxW = 100;

//    std::cout << "llegamos";

    backpack(weights, values, maxW);

    std::cout << best_benefit << "\n";
    print_sol();

    return 0;

}
