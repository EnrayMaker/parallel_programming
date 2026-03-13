#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

using namespave std;

tempalate <typename T>
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

}
