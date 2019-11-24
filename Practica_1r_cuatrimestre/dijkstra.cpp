#include <iostream>
#include "leftistHeap.h"
#include "WUGraph.h"

int main() { 

    // Checker for leftistHeap use, seems to work, missing decreaseKey()
    // LeftistHeap h; 
    // LeftistHeap h1; 
    // LeftistHeap h2; 
    // int x; 
    // int arr[]= {1, 5, 7, 10, 15}; 
    // int arr1[]= {22, 75}; 
  
    // h.insert(arr[0]); 
    // h.insert(arr[1]); 
    // h.insert(arr[2]); 
    // h.insert(arr[3]); 
    // h.insert(arr[4]); 
    // h1.insert(arr1[0]); 
    // h1.insert(arr1[1]); 
  
    // h.deleteMin(x); 
    // std::cout << x << std::endl; 
  
    // h1.deleteMin(x); 
    // std::cout << x << std::endl; 
  
    // h.merge(h1); 
    // h2 = h; 
  
    // h2.deleteMin(x); 
    // std::cout << x << std::endl; 

    WUGraph g1;
    g1.addEdge(0, 1, 3);
    g1.addEdge(0, 2, 5);
    g1.addEdge(2, 1, 2);
    g1.addEdge(0, 3, 1);
    g1.addEdge(3, 4, 7);
    g1.addEdge(4, 5, 6);
    g1.addEdge(1, 5, 3);
    g1.printGraph();
  
    return 0; 
} 