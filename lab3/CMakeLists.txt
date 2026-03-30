cmake_minimum_required(VERSION 3.10)
project(MatrixMultiplication_MPI)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(matrix_mult main.cpp)

target_link_libraries(matrix_mult PUBLIC MPI::MPI_CXX)
