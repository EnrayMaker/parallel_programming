#include "matrix.hpp"
#include <chrono>
#include <iostream>

void runCudaMultiply(const int* h_A, const int* h_B, int* h_C, int N, int blockSize);

int main(int argc, char* argv[]) {
    size_t n = (argc > 1) ? std::stoul(argv[1]) : 1024;
    int blockSize = (argc > 2) ? std::stoi(argv[2]) : 16;

    Matrix<int> m1(n);
    Matrix<int> m2(n);
    Matrix<int> res(n);

    m1.fillRandom(1, 10, 8);
    m2.fillRandom(1, 10, 45);

    auto start = std::chrono::high_resolution_clock::now();

    runCudaMultiply(m1.get_raw_data(), m2.get_raw_data(), res.get_raw_data(), n, blockSize);

    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "N: " << n << " | Block: " << blockSize << "x" << blockSize 
              << " | Time: " << ms << " ms" << std::endl;

    return 0;
}
