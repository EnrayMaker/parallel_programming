import numpy as np
import sys

def main():
    if len(sys.argv) < 3:
        sys.exit(1)

    with open(sys.argv[1], 'r') as f:
        raw_input = [float(x) for x in f.read().split() if x.lstrip('-').replace('.', '', 1).isdigit()]
    
    n = int(np.sqrt(len(raw_input) / 2))
    
    a = np.array(raw_input[:n*n]).reshape(n, n)
    b = np.array(raw_input[n*n:]).reshape(n, n)

    # 2. Читаем числа из result.txt
    with open(sys.argv[2], 'r') as f:
        raw_result = [float(x) for x in f.read().split() if x.lstrip('-').replace('.', '', 1).isdigit()]
    
    res_cpp = np.array(raw_result[:n*n]).reshape(n, n)

    expected = np.dot(a, b)

    if np.allclose(res_cpp, expected, atol=1e-5):
        print("Status - SUCCESS")
        sys.exit(0)
    else:
        print("Status - FAILURE")
        sys.exit(1)

if __name__ == "__main__":
    main()
