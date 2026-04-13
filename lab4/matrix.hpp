#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

template <typename T>
class Matrix {
  std::vector<T> arr;
  size_t N;

public:
  Matrix(size_t size) : N(size), arr(size * size, 0) {}

  //Чтение из файла
  void loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    for (auto& val : arr) in >> val;
  }

  T* get_raw_data() { return arr.data(); }
  const T* get_raw_data() const { return arr.data(); }

  // Заполнение значениями
  void fillRandom(T min, T max, unsigned int seed) {
    std::mt19937 gen(seed);
    if constexpr (std::is_integral_v<T>) {
      std::uniform_int_distribution<T> dist(min, max);
      for (auto& val : arr) val = dist(gen);
    } else {
      std::uniform_real_distribution<T> dist(min, max);
      for (auto& val : arr) val = dist(gen);
    }
  }

  T& operator()(size_t i, size_t j) { return arr[i * N + j]; }
  const T& operator()(size_t i, size_t j) const { return arr[i * N + j]; }
  size_t size() const { return N; }

  Matrix<T> operator*(const Matrix<T>& m) const {
    Matrix<T> res(N);
    for (size_t i = 0; i < N; i++) {
      for (size_t k = 0; k < N; k++) {
        for (size_t j = 0; j < N; j++) {
          res(i, j) += (*this)(i, k) * m(k, j);
        }
      }
    }
    return res;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    for (size_t i = 0; i < m.N; i++) {
      for (size_t j = 0; j < m.N; j++) os << m(i, j) << " ";
      os << "\n";
    }
    return os;
  }
};
