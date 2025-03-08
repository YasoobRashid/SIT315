#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

const int N = 750; 

// Function to generate a random matrix
void generateMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10; // Random numbers between 0-9
}

// Function to multiply matrices sequentially
void multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Initialize matrices
    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N, 0));

    // Generate random matrices
    generateMatrix(A);
    generateMatrix(B);

    // Start timing
    auto start = high_resolution_clock::now();

    // Perform matrix multiplication
    multiplyMatrices(A, B, C);

    // Stop timing
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Print execution time
    cout << "Sequential Execution Time: " << duration.count() << " ms" << endl;

    return 0;
}
