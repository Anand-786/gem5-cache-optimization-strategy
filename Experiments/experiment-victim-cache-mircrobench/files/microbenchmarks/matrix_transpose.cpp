// matrix_transpose_progress.cpp - Classic victim cache scenario with progress
#include <iostream>
#include <chrono>

#define SIZE 256            // Reduced from 512 to 256 for faster gem5 simulation
#define PROGRESS_INTERVAL 32  // Print progress every 32 rows (256/8 = 8 updates)

int main() {
    std::cout << "=== MATRIX TRANSPOSE VICTIM CACHE TEST ===" << std::endl;
    std::cout << "Matrix size: " << SIZE << "x" << SIZE << std::endl;
    
    int** matrix_a = new int*[SIZE];
    int** matrix_b = new int*[SIZE];
    
    std::cout << "Allocating matrices..." << std::endl;
    for(int i = 0; i < SIZE; i++) {
        matrix_a[i] = new int[SIZE];
        matrix_b[i] = new int[SIZE];
    }
    
    std::cout << "Initializing matrices..." << std::endl;
    // Initialize matrix with progress
    for(int i = 0; i < SIZE; i++) {
        if(i % (SIZE/4) == 0) {
            std::cout << "Init progress: " << (i * 100 / SIZE) << "%" << std::endl;
        }
        
        for(int j = 0; j < SIZE; j++) {
            matrix_a[i][j] = i * SIZE + j;
            matrix_b[i][j] = 0;
        }
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Starting matrix transpose..." << std::endl;
    
    // Transpose with detailed progress - causes lots of cache conflicts
    for(int i = 0; i < SIZE; i++) {
        // Progress indicator every PROGRESS_INTERVAL rows
        if(i % PROGRESS_INTERVAL == 0) {
            std::cout << "Transpose progress: Row " << i << "/" << SIZE 
                      << " (" << (i * 100 / SIZE) << "%)" << std::endl;
        }
        
        for(int j = 0; j < SIZE; j++) {
            matrix_b[j][i] = matrix_a[i][j];  // Non-sequential access pattern
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "=== TRANSPOSE COMPLETED ===" << std::endl;
    std::cout << "Transpose time: " << duration.count() << "ms" << std::endl;
    
    // Verification
    std::cout << "Verifying results..." << std::endl;
    bool correct = true;
    for(int i = 0; i < SIZE && correct; i++) {
        for(int j = 0; j < SIZE && correct; j++) {
            if(matrix_b[j][i] != matrix_a[i][j]) {
                correct = false;
            }
        }
    }
    
    std::cout << "Verification: " << (correct ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Sample values:" << std::endl;
    std::cout << "  matrix_a[0][0] = " << matrix_a[0][0] << std::endl;
    std::cout << "  matrix_b[0][0] = " << matrix_b[0][0] << std::endl;
    std::cout << "  matrix_a[1][0] = " << matrix_a[1][0] << std::endl;
    std::cout << "  matrix_b[0][1] = " << matrix_b[0][1] << std::endl;
    
    std::cout << "Final checksum: " << matrix_b[0][0] + matrix_b[SIZE-1][SIZE-1] << std::endl;
    
    std::cout << "Cleaning up memory..." << std::endl;
    // Cleanup
    for(int i = 0; i < SIZE; i++) {
        delete[] matrix_a[i];
        delete[] matrix_b[i];
    }
    delete[] matrix_a;
    delete[] matrix_b;
    
    std::cout << "=== MATRIX TRANSPOSE TEST COMPLETED ===" << std::endl;
    return 0;
}