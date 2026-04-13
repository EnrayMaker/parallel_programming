cmake_minimum_required(VERSION 3.10)
project(MatrixMult_CUDA LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(matrix_cuda main.cpp kernel.cu)

set_target_properties(matrix_cuda PROPERTIES CUDA_SEPARATE_COMPILATION ON)
