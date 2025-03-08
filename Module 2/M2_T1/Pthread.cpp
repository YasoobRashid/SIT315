#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <thread>

using namespace std;
using namespace std::chrono;

const int N = 750; // Matrix size
const int MAX_THREADS = 8; // Number of threads

vector<vector<int>> A(N, vector<int>(N));
vector<vector<int>> B(N, vector<int>(N));
vector<vector<int>> C(N, vector<int>(N, 0));

// Function to generate a random matrix
void generateMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10; // Random numbers between 0-9
}

void multiplyPartial(int start_row, int end_row) {
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void threadedMultiplication(int num_threads) {
    vector<thread> threads;
    int rows_per_thread = N / num_threads;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < num_threads; i++) {
        int start_row = i * rows_per_thread;
        int end_row = (i == num_threads - 1) ? N : (i + 1) * rows_per_thread;
        threads.push_back(thread(multiplyPartial, start_row, end_row));
    }

    for (auto &t : threads) {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "C++ Threads Execution Time with " << num_threads << " threads: " << duration.count() << " ms" << endl;
}

int main() {
    generateMatrix(A);
    generateMatrix(B);

    // Running sequential version for comparison
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

    // Running parallel version with different thread counts
    for (int t = 2; t <= MAX_THREADS; t *= 2) {
        threadedMultiplication(t);
    }

    return 0;
}