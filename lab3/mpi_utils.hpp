#ifndef MPI_UTILS_HPP
#define MPI_UTILS_HPP

#include "matrix.hpp"
#include <mpi.h>
#include <vector>

template <typename T>
void multiplyMPI(const Matrix<T>& m1, const Matrix<T>& m2, Matrix<T>& res, int rank, int size) {
    size_t n = m1.size();
    int rows_per_proc = n / size;

    std::vector<T> local_a(rows_per_proc * n);
    std::vector<T> local_res(rows_per_proc * n, 0);
    std::vector<T> b_flat(n * n);

    if (rank == 0) {
        for (size_t i = 0; i < n * n; i++) b_flat[i] = m2.get_raw_data()[i];
    }

    MPI_Bcast(b_flat.data(), n * n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(rank == 0 ? m1.get_raw_data() : nullptr, rows_per_proc * n, MPI_INT,
                local_a.data(), rows_per_proc * n, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows_per_proc; ++i) {
        for (size_t k = 0; k < n; ++k) {
            for (size_t j = 0; j < n; ++j) {
                local_res[i * n + j] += local_a[i * n + k] * b_flat[k * n + j];
            }
        }
    }

    MPI_Gather(local_res.data(), rows_per_proc * n, MPI_INT,
               rank == 0 ? res.get_raw_data() : nullptr, rows_per_proc * n, MPI_INT, 0, MPI_COMM_WORLD);
}

#endif
