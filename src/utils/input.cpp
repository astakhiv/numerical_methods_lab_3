#include "./input.h"
#include <iostream>
#include <vector>

ld eps = 1e-11;
int precision = 11;

void readVector(ull n, std::vector<ld> &B) {
  for (ull i = 0; i < n; i++) {
    std::cin >> B[i];
  }
}

void readMatrix(ull n, std::vector<std::vector<ld>> &A) {
  for (ull i = 0; i < n; i++) {
    for (ull j = 0; j < n; j++) {
      std::cin >> A[i][j];
    }
  }
}
