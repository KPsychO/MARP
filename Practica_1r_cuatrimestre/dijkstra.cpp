#include "leftistHeap.h"
#include <iostream>

int main() { 
    LeftistHeap h; 
    LeftistHeap h1; 
    LeftistHeap h2; 
    int x; 
    int arr[]= {1, 5, 7, 10, 15}; 
    int arr1[]= {22, 75}; 
  
    h.insert(arr[0]); 
    h.insert(arr[1]); 
    h.insert(arr[2]); 
    h.insert(arr[3]); 
    h.insert(arr[4]); 
    h1.insert(arr1[0]); 
    h1.insert(arr1[1]); 
  
    h.deleteMin(x); 
    std::cout << x << std::endl; 
  
    h1.deleteMin(x); 
    std::cout << x << std::endl; 
  
    h.merge(h1); 
    h2 = h; 
  
    h2.deleteMin(x); 
    std::cout << x << std::endl; 
  
    return 0; 
} 