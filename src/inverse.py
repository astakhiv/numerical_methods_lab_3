import sys
import io
import numpy as np
# load data
print("inverse.py")

input_file = sys.argv[1]

with open(input_file, "r") as inp, open("/tmp/inverse.in", "w") as inv:
    omega = np.float64(inp.readline().strip())
    n = int(inp.readline().strip())

    A = np.zeros((n, n))
    for i in range(n):
        A[i] = np.array(inp.readline().split(), dtype=np.float64)

    L = np.tril(A, -1)
    R = np.triu(A, 1)
    D = A - (L + R)

    C = np.linalg.inv(D + omega * L)

    inp.seek(0, io.SEEK_END)

    for r in C:
        row_str = np.char.mod("%f", r)
        inv.write(" ".join(row_str) + "\n")
