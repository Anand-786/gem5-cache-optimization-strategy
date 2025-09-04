// matrix_transpose.cpp - Classic victim cache scenario
#include <iostream>
#include <chrono>

#define SIZE 512  // 512x512 matrix

int main() {
    int** matrix_a = new int*[SIZE];
    int** matrix_b = new int*[SIZE];
    
    for(int i = 0; i < SIZE; i++) {
        matrix_a[i] = new int[SIZE];
        matrix_b[i] = new int[SIZE];
    }
    
    // Initialize matrix
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            matrix_a[i][j] = i * SIZE + j;
            matrix_b[i][j] = 0;
        }
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Transpose - causes lots of cache conflicts
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            matrix_b[j][i] = matrix_a[i][j];  // Non-sequential access pattern
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Transpose time: " << duration.count() << "ms" << std::endl;
    std::cout << "Checksum: " << matrix_b[0][0] + matrix_b[SIZE-1][SIZE-1] << std::endl;
    
    // Cleanup
    for(int i = 0; i < SIZE; i++) {
        delete[] matrix_a[i];
        delete[] matrix_b[i];
    }
    delete[] matrix_a;
    delete[] matrix_b;
    
    return 0;
}