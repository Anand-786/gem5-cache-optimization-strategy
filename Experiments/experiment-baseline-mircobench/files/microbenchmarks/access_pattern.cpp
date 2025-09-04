// victim_test1.cpp - Cache conflict with temporal reuse
#include <iostream>
#include <chrono>

#define ARRAY_SIZE (64 * 1024)  // 64K elements (256KB for int)
#define ITERATIONS 1000

int main() {
    int* array = new int[ARRAY_SIZE];
    
    // Initialize
    for(int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Pattern that creates victim cache opportunities
    for(int iter = 0; iter < ITERATIONS; iter++) {
        // First pass - evict data from L1
        for(int i = 0; i < ARRAY_SIZE; i += 16) {  // Stride to cause conflicts
            array[i] = array[i] + 1;
        }
        
        // Second pass - access recently evicted data (victim cache opportunity)
        for(int i = 0; i < ARRAY_SIZE; i += 16) {
            array[i] = array[i] * 2;  // These could hit in victim cache
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Execution time: " << duration.count() << "ms" << std::endl;
    std::cout << "Final checksum: " << array[0] + array[ARRAY_SIZE-1] << std::endl;
    
    delete[] array;
    return 0;
}