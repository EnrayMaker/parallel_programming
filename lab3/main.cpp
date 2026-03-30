#include "matrix.hpp"
#include "mpi_utils.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    size_t n = (argc > 1) ? std::stoul(argv[1]) : 100;

    Matrix<int> m1(n);
    Matrix<int> m2(n);
    Matrix<int> res(n);

    if (rank == 0) {
        m1.fillRandom(1, 10, 8);
        m2.fillRandom(1, 10, 45);
        
        std::ofstream out_in("input.txt");
        out_in << "Matrix A:\n" << m1 << "Matrix B:\n" << m2;
        out_in.close();
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    // Вместо res = m1 * m2
    multiplyMPI(m1, m2, res, rank, size);

    if (rank == 0) {
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::ofstream out_res("result.txt");
        out_res << "Result Matrix:\n" << res << "\nTime: " << ms << " ms";
        out_res.close();

        std::cout << "Size: " << n << " | Procs: " << size << " | Time: " << ms << " ms" << std::endl;
        std::system("python3 ../verify.py input.txt result.txt");
    }

    MPI_Finalize();
    return 0;
}
