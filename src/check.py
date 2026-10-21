import sys
import numpy as np
# load data
print("check.py")

CONVERGES = 0
BAD_EIGENVALUES = 5

print(sys.argv)
input_file = sys.argv[1]
output_file = sys.argv[2]

with open(input_file, "r") as inp, open(output_file, "w") as out:
    omega = np.float64(inp.readline().strip())
    n = int(inp.readline().strip())

    A = np.zeros((n, n))
    for i in range(n):
        A[i] = np.array(inp.readline().split(), dtype=np.float64)

    L = np.tril(A, -1)
    R = np.triu(A, 1)
    D = A - (L + R)

    C = np.linalg.inv(D + omega * L) @ ((1-omega) * D - omega * R)

    eigen_values = np.linalg.eigvals(C)
    abs_eigen_values = np.abs(eigen_values)

    # check eigenvalues
    for eigen_value in abs_eigen_values:
        if eigen_value >= 1.0:
            out.write(f"The C_omega has {
                      eigen_value} as eigen values, diverges.")
            sys.exit(BAD_EIGENVALUES)


# on success
sys.exit(CONVERGES)
