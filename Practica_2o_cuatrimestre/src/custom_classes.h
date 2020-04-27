#include <queue>        // std::priority_queue
#include <vector>       // std::vector
#include <algorithm>    // std::max
#include <iostream>     // std::cout

class Node {

    public:
        std::vector<bool> _sol;
        long unsigned int _k;
        float _weight, _benefit, _optimal_benefit;

        friend bool operator<(const Node &n, const Node &m) { return (n._optimal_benefit < m._optimal_benefit); }
        friend bool operator>(const Node &n, const Node &m) { return (m < n); }
        friend bool operator<=(const Node &n, const Node &m) { return !(n > m); }
        friend bool operator>=(const Node &n, const Node &m) { return !(n < m); }

};

class MyPair {

    public:
        std::pair<float, float> _elem;

        friend bool operator<(const MyPair &n, const MyPair &m) { return ((n._elem.first/n._elem.second) < (m._elem.first/m._elem.second)); }
        friend bool operator>(const MyPair &n, const MyPair &m) { return (m < n); }
        friend bool operator<=(const MyPair &n, const MyPair &m) { return !(n > m); }
        friend bool operator>=(const MyPair &n, const MyPair &m) { return !(n < m); }

        MyPair() {};

        MyPair(std::pair<float, float> elem) {
        	_elem = elem;
        }


        float value() { return _elem.first; }
        float weight() { return _elem.second; }

};
