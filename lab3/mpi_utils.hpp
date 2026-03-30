#ifndef MPI_UTILS_HPP
#define MPI_UTILS_HPP

#include <vector>
#include <mpi.h>

void multiplyMPI(int n, const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& res) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_proc = n / size;
    std::vector<int> local_a(rows_per_proc * n);
    std::vector<int> local_res(rows_per_proc * n, 0);
    
    std::vector<int> b_buffer = b; 
    if (rank != 0) b_buffer.resize(n * n);

    MPI_Bcast(b_buffer.data(), n * n, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(a.data(), rows_per_proc * n, MPI_INT, 
                local_a.data(), rows_per_proc * n, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows_per_proc; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) {
                local_res[i * n + j] += local_a[i * n + k] * b_buffer[k * n + j];
            }
        }
    }

    MPI_Gather(local_res.data(), rows_per_proc * n, MPI_INT, 
               res.data(), rows_per_proc * n, MPI_INT, 0, MPI_COMM_WORLD);
}

#endif
