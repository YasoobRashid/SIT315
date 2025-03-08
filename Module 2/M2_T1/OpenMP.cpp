#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int N = 750;

// Function to generate a random matrix
void generateMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10; // Random numbers between 0-9
}

// Function to multiply matrices using OpenMP parallelization
void multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C) {
    #pragma omp parallel for collapse(2)
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
    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N, 0));

    generateMatrix(A);
    generateMatrix(B);

    auto start_seq = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto stop_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<milliseconds>(stop_seq - start_seq);
    cout << "Sequential Execution Time: " << duration_seq.count() << " ms" << endl;

    auto start_omp = high_resolution_clock::now();
    multiplyMatrices(A, B, C);
    auto stop_omp = high_resolution_clock::now();
    auto duration_omp = duration_cast<milliseconds>(stop_omp - start_omp);
    cout << "OpenMP Execution Time: " << duration_omp.count() << " ms" << endl;

    return 0;
}

