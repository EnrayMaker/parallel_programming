import numpy as np
import sys

def check():
    try:
        # Читаем входные данные
        with open(sys.argv[1], 'r') as f:
            n = int(f.readline())
            data = np.fromstring(f.read(), sep=' ')
            m1 = data[:n*n].reshape(n, n)
            m2 = data[n*n:].reshape(n, n)

        # Читаем результат C++
        res_cpp = np.loadtxt(sys.argv[2]).reshape(n, n)
        
        # Считаем эталон
        res_real = np.dot(m1, m2)

        if np.allclose(res_cpp, res_real):
            print("--- Verification: SUCCESS ---")
            sys.exit(0)
        else:
            print("--- Verification: FAILED ---")
            sys.exit(1)
    except Exception as e:
        print(f"Error during verification: {e}")
        sys.exit(1)

if __name__ == "__main__":
    check()
