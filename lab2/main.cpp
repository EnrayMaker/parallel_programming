#include "matrix.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <omp.h>

int main(int argc, char* argv[]) {
    size_t n = (argc > 1) ? std::stoul(argv[1]) : 100;
    int threads = (argc > 2) ? std::stoi(argv[2]) : 4;

    omp_set_num_threads(threads);

    Matrix<int> m1(n);
    Matrix<int> m2(n);
    
    m1.fillRandom(1, 100, 8);
    m2.fillRandom(-50, 150, 45);

    std::ofstream out_in("input.txt");
    if (out_in.is_open()) {
        out_in << "Matrix A:\n" << m1;
        out_in << "Matrix B:\n" << m2;
        out_in.close();
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto res = m1 * m2;
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed_ms = duration.count() / 1000.0;

    std::ofstream out_res("result.txt");
    if (out_res.is_open()) {
        out_res << "Result Matrix:\n" << res << "\n";
        out_res << "Size: " << n << "x" << n << "\n";
        out_res << "Time: " << elapsed_ms << " ms" << std::endl;
        out_res.close();
    }

    std::cout << "Finished. Size: " << n << "x" << n << " | Threads: " << threads << " | Time: " << elapsed_ms << " ms" << std::endl;

    if (n <= 1000) {
        std::string cmd = "python3 ../verify.py input.txt result.txt";
        int check = std::system(cmd.c_str());

        if (check == 0) {
            std::cout << "Status: Verification Success" << std::endl;
        } else {
            std::cout << "Status: Verification Failure" << std::endl;
        }
    } else {
        std::cout << "Status: Verification Skipped (Size too large)" << std::endl;
    }

    return 0;
}
