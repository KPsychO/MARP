#include <iostream>
#include "leftistHeap.h"
#include "WDGraph.h"

void dijkstra(WDGraph g, int src) {

    LeftistHeap h;

    // dist[g._nVertex] = g.getVertexs();
    // // for (int i = 0; i < g._nVertex; i++){
    // //     if (dist[i]->elem() != src)
    // //         h.insert(std::make_pair(dist[i]->dist(), dist[i]->elem()));
    // // }
    // g.changeVertexDistance(src, 0);
    // g.visitVertex(src);

    // std::pair<int, float> neightbours[g.getNumberOfNeightbours(src)] = g.getNeightbours(src);

    // for (int i = 0; i < g.getNumberOfNeightbours(src); i++){
    //     g.changeVertexDistance(neightbours[i].first, neightbours[i].second);
    //     h.insert(std::make_pair(neightbours[i].second, neightbours[i].first));
    // }

    // while (!h.isEmpty()){
    //     std::pair<float, int> elem;
    //     h.deleteMin(elem);
    //     g.visitVertex(elem);
    //     neightbours = g.getNeightbours(elem.second);

    //     for (int i = 0; i < g.getNumberOfNeightbours(elem.second); i++){
    //         g.changeVertexDistance(neightbours[i].first, neightbours[i].second);
    //         h.insert(std::make_pair(neightbours[i].second, neightbours[i].first));
    //     }

    // }



}

int main() { 

    // h.insert(std::make_pair(19, 76));
    // h.insert(std::make_pair(23, 62));
    // h.insert(std::make_pair(41, 43));
    // h.insert(std::make_pair(34, 12));
    // h.insert(std::make_pair(22, 2));
    // h.insert(std::make_pair(43, 32));

    // h.printHeap();

    // h.decreaseKey(41, 16);

    // h.printHeap();

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
    // g.printGraph();
    // g.printGraphVertexs();



  
    return 0; 
} 