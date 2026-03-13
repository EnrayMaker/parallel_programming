#include "Matrix.hpp"
#include <chrono>

int main(int argc, char* argv[]) {
  size_t n = (argc > 1) ? std::stoi(argv[1]) : 10;

  Matrix<int> m1(n);
  Matrix<int> m2(n);
  m1.fillRandom(1, 10, 8);
  m2.fillRandom(1, 10, 45);

  std::ofstream out_in("input.txt");
  out_in << n << "\n" << m1 << m2;
  out_in.close();

  auto start = std::chrono::high_resolution_clock::now();
  auto res = m1 * m2;
  auto end = std::chrono::high_resolution_clock::now();

  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::ofstream out_res("result.txt");
  out_res << res;
  out_res.close();

  std::cout << "size: " << n << "x" << n << " | Time: " << time.count() << " ms" << std::endl;
  
  int check = std::system("python3 verify.py input.txt result.txt");
  return 0;
}
