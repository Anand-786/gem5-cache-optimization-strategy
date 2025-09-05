// victim_test1_small.cpp - Reduced size with progress indicators
#include <iostream>

#define ARRAY_SIZE (64 * 1024)  // Reduced from 64K to 16K elements
#define ITERATIONS 1000          // Reduced from 1000 to 100
#define PROGRESS_INTERVAL 10    // Print every 10 iterations

int main() {
    int* array = new int[ARRAY_SIZE];
    
    // Initialize
    for(int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    
    std::cout << "Starting victim cache test..." << std::endl;
    std::cout << "Array size: " << ARRAY_SIZE << " elements" << std::endl;
    std::cout << "Iterations: " << ITERATIONS << std::endl;
    
    // Pattern that creates victim cache opportunities
    for(int iter = 0; iter < ITERATIONS; iter++) {
        // Progress indicator
        if(iter % PROGRESS_INTERVAL == 0) {
            std::cout << "Iteration " << iter << "/" << ITERATIONS 
                      << " (" << (iter * 100 / ITERATIONS) << "%)" << std::endl;
        }
        
        // First pass - evict data from L1
        for(int i = 0; i < ARRAY_SIZE; i += 16) {  // Stride to cause conflicts
            array[i] = array[i] + 1;
        }
        
        // Second pass - access recently evicted data (victim cache opportunity)
        for(int i = 0; i < ARRAY_SIZE; i += 16) {
            array[i] = array[i] * 2;  // These could hit in victim cache
        }
    }
    
    std::cout << "Test completed!" << std::endl;
    std::cout << "Final checksum: " << array[0] + array[ARRAY_SIZE-1] << std::endl;
    
    delete[] array;
    return 0;
}