#include "./utils/cmp.h"
#include "./utils/definitions.h"
#include "./utils/input.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

const ull maxIter = 50000;

void SOR_iteration(ull n, ld omega, std::vector<std::vector<ld>> &A,
                   std::vector<ld> &B, std::vector<ld> &X_0,
                   std::vector<ld> &X);

void printLInfNorm(ull n, std::vector<std::vector<ld>> &A, std::vector<ld> &B,
                   std::vector<ld> &X);

ld l_inf(ull n, std::vector<ld> &A) {
  ld max_val = 0;

  for (ull i = 0; i < n; i++) {
    max_val = std::max(max_val, std::abs(A[i]));
  }

  return max_val;
}

void diff(ull n, std::vector<ld> &A, std::vector<ld> &B, std::vector<ld> &ans) {
  for (ull i = 0; i < n; i++) {
    ans[i] = std::abs(A[i] - B[i]);
  }
}

ld row_norm(ull n, std::vector<std::vector<ld>> &C);
ld col_norm(ull n, std::vector<std::vector<ld>> &C);

int inverse(ull n, std::vector<std::vector<ld>> &A);

int main(int argc, char *argv[]) {
  std::cout << "SOR.cpp" << std::endl;

  freopen(argv[1], "r", stdin);
  freopen(argv[2], "w", stdout);

  // load omega
  ld omega;
  std::cin >> omega;

  // load matrix

  ull n;
  std::cin >> n;
  std::vector<std::vector<ld>> A(n, std::vector<ld>(n, 0));
  std::vector<std::vector<ld>> C(n, std::vector<ld>(n, 0));
  std::vector<ld> B(n, 0), X(n, 0), X_0(n, 0), vec_diff(n, 0);

  readMatrix(n, A);
  readVector(n, B);
  readVector(n, X_0);

  freopen("/tmp/inverse.in", "r", stdin);
  readMatrix(n, C);

  // ld q = row_norm(n, C);

  // SOR_iteration(n, omega, A, B, X_0, X);

  // if (q < 1) {
  //   diff(n, X, X_0, vec_diff);
  //   ull k =
  //       std::ceil(std::log(eps * (1.0 - q) / l_inf(n, vec_diff)) /
  //       std::log(q));
  //   std::cout << "Upper k limit: " << k << std::endl;
  // } else {
  //   std::cout << "Can't approximate number of iterations" << std::endl;
  // }

  // if (q >= 1) {
  //   q = 0.5;
  // }

  // ld cmp = (1 - q) / q * eps;
  // ull i;
  // for (i = 0; i < maxIter; i++) {

  //   diff(n, X, X_0, vec_diff);
  //   ld norm = l_inf(n, vec_diff);

  //   if (norm <= cmp || isZero(norm - cmp)) {
  //     break;
  //   }

  //   swap(X, X_0);
  //   SOR_iteration(n, omega, A, B, X_0, X);

  //   if (i == maxIter - 1) {
  //     std::cout << "Presision was not reached" << std::endl;
  //   }
  // }

  // std::cout << "Actual iteration: " << i + 1 << std::endl;
  // for (ull i = 0; i < n; i++) {
  //   std::cout << X[i] << " ";
  // }
  // std::cout << std::endl;

  // printLInfNorm(n, A, B, X);

  return 0;
}

void SOR_iteration(ull n, ld omega, std::vector<std::vector<ld>> &A,
                   std::vector<ld> &B, std::vector<ld> &X_0,
                   std::vector<ld> &X) {
  for (ull i = 0; i < n; i++) {
    ld z_i = B[i];

    for (ull j = 0; j < i; j++) {
      z_i -= A[i][j] * X[j];
    }

    for (ull j = i + 1; j < n; j++) {
      z_i -= A[i][j] * X_0[j];
    }

    z_i /= A[i][i];

    X[i] = (1 - omega) * X_0[i] + omega * z_i;
  }
}

void printLInfNorm(ull n, std::vector<std::vector<ld>> &A, std::vector<ld> &B,
                   std::vector<ld> &X) {
  std::vector<ld> B_tick(n);
  for (ull i = 0; i < n; i++) {
    ld b_tick = 0;
    for (ull j = 0; j < n; j++) {
      b_tick += A[i][j] * X[j];
    }
    B_tick[i] = B[i] - b_tick;
  }

  std::cout << "lInf: " << l_inf(n, B_tick) << "\n";
}

ld row_norm(ull n, std::vector<std::vector<ld>> &C) {
  ld max_val = 0;

  for (ull i = 0; i < n; i++) {
    ld sum = 0;
    for (ull j = 0; j < n; j++) {
      sum += std::abs(C[i][j]);
    }
    max_val = std::max(max_val, sum);
  }

  return max_val;
}

ld col_norm(ull n, std::vector<std::vector<ld>> &C) {
  ld max_val = 0;

  for (ull j = 0; j < n; j++) {
    ld sum = 0;
    for (ull i = 0; i < n; i++) {
      sum += std::abs(C[i][j]);
    }
    max_val = std::max(max_val, sum);
  }

  return max_val;
}
