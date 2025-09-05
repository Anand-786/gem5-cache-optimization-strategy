// victim_test_tiny.cpp - Very small for quick testing
#include <iostream>

#define ARRAY_SIZE 1024         // Just 1K elements
#define ITERATIONS 50           // Only 50 iterations

int main() {
    int* array = new int[ARRAY_SIZE];
    
    std::cout << "=== TINY VICTIM CACHE TEST START ===" << std::endl;
    
    // Initialize
    for(int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    
    std::cout << "Initialization done. Starting main loop..." << std::endl;
    
    for(int iter = 0; iter < ITERATIONS; iter++) {
        if(iter % 10 == 0) {
            std::cout << "Iter " << iter << std::endl;
        }
        
        // Create cache conflicts
        for(int i = 0; i < ARRAY_SIZE; i += 8) {
            array[i] += 1;
        }
        
        // Access recently evicted data
        for(int i = 0; i < ARRAY_SIZE; i += 8) {
            array[i] *= 2;
        }
    }
    
    std::cout << "=== TEST COMPLETED ===" << std::endl;
    std::cout << "Checksum: " << array[0] + array[ARRAY_SIZE-1] << std::endl;
    
    delete[] array;
    return 0;
}