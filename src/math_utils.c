#include "math_utils.h"

#include "constants.h"

uint64_t factorial(int n) {
  if (n < 0 || n > MAX_FACTORIAL_INPUT) {
    return 0;
  }
  uint64_t result = 1;
  for (int i = 1; i <= n; i++) {
    result *= (uint64_t)i;
  }
  return result;
}

uint64_t permutations(int n, int r) {
  if (n < 0 || r < 0 || r > n) {
    return 0;
  }
  uint64_t result = 1;
  for (int i = 0; i < r; i++) {
    result *= (uint64_t)(n - i);
  }
  return result;
}

bool safe_mul_div(uint64_t *acc, uint64_t mul, uint64_t div) {
  __uint128_t temp = (__uint128_t)(*acc) * mul;
  temp /= div;
  if (temp > UINT64_MAX) return false;
  *acc = (uint64_t)temp;
  return true;
}

uint64_t combinations(int n, int r) {
  if (n < 0 || r < 0 || r > n) {
    return 0;
  }

  if (r > n / 2) {
    r = n - r;
  }

  uint64_t result = 1;
  for (int i = 1; i <= r; i++) {
    uint64_t mul = (uint64_t)(n - i + 1);
    uint64_t div = (uint64_t)i;
    if (!safe_mul_div(&result, mul, div)) {
      return 0;
    }
  }
  return result;
}
