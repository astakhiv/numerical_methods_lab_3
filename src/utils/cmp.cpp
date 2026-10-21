#include "./cmp.h"

bool isZero(ld val) {
  // absolute comparison for zero
  return std::abs(val) < eps;
}
