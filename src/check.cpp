#include "./utils/cmp.h"
#include "./utils/definitions.h"
#include "./utils/input.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

bool choleskyDecompositionPossible(ull n, std::vector<std::vector<ld>> &A);

int main(int argc, char *argv[]) {
  std::cout << "check.cpp" << std::endl;

  freopen(argv[1], "r", stdin);
  freopen(argv[2], "w", stdout);

  // load omega
  ld omega;
  std::cin >> omega;

  // Omega check
  if (omega <= 0 || omega >= 2) {
    fprintf(stdout, "omega=%lf must be in (0; 2)\n", omega);
    return BAD_OMEGA;
  }

  // load matrix

  ull n;
  std::cin >> n;
  std::vector<std::vector<ld>> A(n, std::vector<ld>(n, 0));

  readMatrix(n, A);

  // Zero diagonal check
  for (ull i = 0; i < n; i++) {
    if (isZero(A[i][i])) {
      fprintf(stdout, "Elements on main diagonal of A must not be 0\n");
      return BAD_DIAGONAL;
    }
  }

  // Diagonal dominance check
  bool diagonal_dominant = true;
  ld max_diag_sum = 0;
  for (ull i = 0; i < n; i++) {
    ld non_diagonal_sum = 0;
    ld abs_diag = std::abs(A[i][i]);
    for (ull j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }

      non_diagonal_sum += std::abs(A[i][j]);

      if (non_diagonal_sum > abs_diag || isZero(non_diagonal_sum - abs_diag)) {
        diagonal_dominant = false;
        break;
      }
    }

    if (diagonal_dominant == false) {
      break;
    }

    non_diagonal_sum = non_diagonal_sum / abs_diag;
    max_diag_sum = std::max(max_diag_sum, non_diagonal_sum);
  }

  if (diagonal_dominant) {
    ld omega_upper_bound = 2.0 / (1.0 + max_diag_sum);
    if (omega < omega_upper_bound && !isZero(omega_upper_bound - omega)) {
      return CONVERGES;
    }
  }

  // Ostrowski-Reich check (symmetry, positive-definitiveness)
  for (ull i = 0; i < n; i++) {
    for (ull j = i + 1; j < n; j++) {
      if (isZero(A[i][j] - A[j][i]) == false) {
        return NON_SPD;
      }
    }
  }

  if (!choleskyDecompositionPossible(n, A)) {
    fprintf(stdout, "Matrix a is symmetric but not positive definite.\n");
    return SNPD;
  }

  return CHECK_EIGEN;
}

bool choleskyDecompositionPossible(ull n, std::vector<std::vector<ld>> &A) {
  std::vector<std::vector<ld>> L(n, std::vector<ld>(n, 0));
  for (ull i = 0; i < n; i++) {
    for (ull j = 0; j < i; j++) {
      ld sum = 0;

      for (ull k = 0; k < j; k++) {
        sum += L[i][k] * L[j][k];
      }

      L[i][j] = ((A[i][j] - sum) / L[j][j]);
    }

    ld sum = 0;

    for (ull k = 0; k < i; k++) {
      sum += L[i][k] * L[i][k];
    }

    sum = A[i][i] - sum;

    if (sum < 0 || isZero(sum)) {
      return false;
    }

    L[i][i] = std::sqrt(sum);
  }

  return true;
}
