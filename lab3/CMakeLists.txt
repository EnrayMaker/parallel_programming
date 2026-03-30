cmake_minimum_required(VERSION 3.10)
project(MatrixMultiplication)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(matrix_mult main.cpp)

target_link_libraries(matrix_mult PUBLIC OpenMP::OpenMP_CXX)
