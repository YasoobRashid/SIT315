#include <chrono>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <thread>
#include <vector>
#include <algorithm>  

using namespace std::chrono;
using namespace std;

void randomVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
}

void vectorAddition(int v1[], int v2[], int v3[], int start, int end){
    for (int i = start; i < end; i++) {
        v3[i] = v1[i] + v2[i];
    }
}

int main() {
  unsigned long size = 100000000; 
  int num_threads = thread::hardware_concurrency();
  srand(time(0));

  int *v1 = (int *)malloc(size * sizeof(int));
  int *v2 = (int *)malloc(size * sizeof(int)); 
  int *v3 = (int *)malloc(size * sizeof(int));  

  randomVector(v1, size);
  randomVector(v2, size);

  vector<thread> threads;
  int chunk_size = size / num_threads;

  auto start = high_resolution_clock::now();

  for (int i = 0; i < num_threads; i++) {
    threads.push_back(thread(vectorAddition, v1, v2, v3, 
        i * chunk_size, std::min((unsigned long)((i + 1) * chunk_size), size)));  
  }

  for (auto &t : threads) {
    t.join();
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  cout << "Time taken by parallel function: " << duration.count() << " microseconds" << endl;

  free(v1);
  free(v2);
  free(v3);

  return 0;
}
