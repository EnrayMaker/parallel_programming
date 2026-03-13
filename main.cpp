#include "matrix.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    size_t n = (argc > 1) ? std::stoul(argv[1]) : 10;

    Matrix<int> m1(n);
    Matrix<int> m2(n);
    
    m1.fillRandom(1, 100, 8);
    m2.fillRandom(-200, 700, 45);

    // Запись входных данных в файл
    std::ofstream out_in("input.txt");
    if (out_in.is_open()) {
        out_in << "matrix A = \n" << m1;
        out_in << "matrix B = \n" << m2;
        out_in.close();
    }

    // Измерение времени и вычисление
    auto start = std::chrono::high_resolution_clock::now();
    auto res = m1 * m2;
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed_ms = duration.count() / 1000.0;

    // Запись результата
    std::ofstream out_res("result.txt");
    if (out_res.is_open()) {
        out_res << "Result = \n" << res << "\n";
        out_res << "Size = " << n << "x" << n << "\n";
        out_res << "Time = " << elapsed_ms << " ms" << std::endl;
        out_res.close();
    }

    std::cout << "Finished Size = " << n << "x" << n << std::endl;

    std::string cmd = "python3 verify.py input.txt result.txt";
    int check = std::system(cmd.c_str());

    if (check == 0) {
        std::cout << "Status - Verif Success" << std::endl;
    } else {
        std::cout << "Status - Verif Failure" << std::endl;
    }

    return 0;
}

