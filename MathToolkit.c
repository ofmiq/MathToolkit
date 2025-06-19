#define _USE_MATH_DEFINES
#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 100
#define MAX_FACTORIAL_INPUT 20
#define TAN_EPSILON 1e-9

/* ======================== Input Utilities ======================== */

/**
 * Read a line from stdin into buffer (strips trailing newline).
 * @return true on success, false on EOF.
 */
static bool read_line(char *buf, size_t bufsize) {
  if (!fgets(buf, bufsize, stdin)) {
    return false;
  }
  size_t len = strlen(buf);
  if (len && buf[len - 1] == '\n') {
    buf[len - 1] = '\0';
  }
  return true;
}

/**
 * Prompt for an integer, parse with strtol.
 * @returns true and sets *out on valid parse, false otherwise.
 */
static bool read_int(const char *prompt, int *out) {
  char line[MAX_LINE_LEN];
  char *endptr;
  long val;

  printf("%s", prompt);
  if (!read_line(line, sizeof(line))) {
    return false;
  }

  errno = 0;
  val = strtol(line, &endptr, 10);
  if (errno != 0 || endptr == line || *endptr != '\0') {
    return false;
  }
  *out = (int)val;
  return true;
}

/**
 * Prompt for a double, parse with strtod.
 * @returns true and sets *out on valid parse, false otherwise.
 */
static bool read_double(const char *prompt, double *out) {
  char line[MAX_LINE_LEN];
  char *endptr;
  double val;

  printf("%s", prompt);
  if (!read_line(line, sizeof(line))) {
    return false;
  }

  errno = 0;
  val = strtod(line, &endptr);
  if (errno != 0 || endptr == line || *endptr != '\0') {
    return false;
  }
  *out = val;
  return true;
}

/* ======================== Math Utilities ======================== */

/**
 * Compute n! for 0 <= n <= MAX_FACTORIAL_INPUT.
 * @returns 0 if n < 0, > MAX_FACTORIAL_INPUT, else n!.
 */
static uint64_t factorial(int n) {
  if (n < 0 || n > MAX_FACTORIAL_INPUT) {
    return 0;
  }
  uint64_t result = 1;
  for (int i = 1; i <= n; i++) {
    result *= (uint64_t)i;
  }
  return result;
}

/**
 * Compute P(n, r) = n! / (n-r)! without overflow detection.
 * @returns 0 if inputs invalid; else P(n, r).
 */
static uint64_t permutations(int n, int r) {
  if (n < 0 || r < 0 || r > n) {
    return 0;
  }
  uint64_t result = 1;
  for (int i = 0; i < r; i++) {
    result *= (uint64_t)(n - i);
  }
  return result;
}

/**
 * Safe multiply and divide: acc = acc * mul / div
 * Checks for 128-bit intermediate overflow.
 * @returns true on success, false if overflow would occur.
 */
static bool safe_mul_div(uint64_t *acc, uint64_t mul, uint64_t div) {
  __uint128_t temp = (__uint128_t)(*acc) * mul;
  temp /= div;
  if (temp > UINT64_MAX) return false;
  *acc = (uint64_t)temp;
  return true;
}

/**
 * Compute C(n, r) = n! / (r!(n-r)!) with overflow detection.
 * @returns 0 if inputs invalid or result overflow.
 */
static uint64_t combinations(int n, int r) {
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

/* ======================== Menu Handlers ======================== */

static void handle_trigonometry(void) {
  const double pi = M_PI;
  while (1) {
    printf(
        "\n--- Trigonometry ---\n"
        "1) sin(x)\n"
        "2) cos(x)\n"
        "3) tan(x)\n"
        "4) arcsin(x)\n"
        "5) arccos(x)\n"
        "6) arctan(x)\n"
        "7) Back\n"
        "Select: ");

    int choice;
    if (!read_int("", &choice)) {
      printf("Invalid selection.\n");
      continue;
    }

    if (choice == 7) {
      return;
    }

    double x, res;
    if (choice >= 1 && choice <= 6) {
      if (!read_double("Enter value: ", &x)) {
        printf("Invalid number.\n");
        continue;
      }
    }

    switch (choice) {
      case 1:
        res = sin(x * pi / 180.0);
        printf("sin(%.4f°) = %.6f\n", x, res);
        break;
      case 2:
        res = cos(x * pi / 180.0);
        printf("cos(%.4f°) = %.6f\n", x, res);
        break;
      case 3: {
        double rem = fmod(x, 180.0);
        if (fabs(rem - 90.0) < TAN_EPSILON) {
          printf("tan(%.4f°) is undefined.\n", x);
        } else {
          res = tan(x * pi / 180.0);
          printf("tan(%.4f°) = %.6f\n", x, res);
        }
        break;
      }
      case 4:
        if (x < -1.0 || x > 1.0) {
          printf("arcsin input must be in [-1,1].\n");
        } else {
          res = asin(x) * 180.0 / pi;
          printf("arcsin(%.4f) = %.6f°\n", x, res);
        }
        break;
      case 5:
        if (x < -1.0 || x > 1.0) {
          printf("arccos input must be in [-1,1].\n");
        } else {
          res = acos(x) * 180.0 / pi;
          printf("arccos(%.4f) = %.6f°\n", x, res);
        }
        break;
      case 6:
        res = atan(x) * 180.0 / pi;
        printf("arctan(%.4f) = %.6f°\n", x, res);
        break;
      default:
        printf("Invalid selection.\n");
    }
  }
}

static void handle_exponential(void) {
  while (1) {
    printf(
        "\n--- Exponential & Logarithm ---\n"
        "1) exp(x)\n"
        "2) ln(x)\n"
        "3) log10(x)\n"
        "4) Back\n"
        "Select: ");

    int choice;
    if (!read_int("", &choice)) {
      printf("Invalid selection.\n");
      continue;
    }

    if (choice == 4) {
      return;
    }

    double x;
    if (!read_double("Enter value: ", &x)) {
      printf("Invalid number.\n");
      continue;
    }

    switch (choice) {
      case 1:
        printf("exp(%.4f) = %.6f\n", x, exp(x));
        break;
      case 2:
        if (x <= 0) {
          printf("ln input must be > 0.\n");
        } else {
          printf("ln(%.4f) = %.6f\n", x, log(x));
        }
        break;
      case 3:
        if (x <= 0) {
          printf("log10 input must be > 0.\n");
        } else {
          printf("log10(%.4f) = %.6f\n", x, log10(x));
        }
        break;
      default:
        printf("Invalid selection.\n");
    }
  }
}

static void handle_powers(void) {
  while (1) {
    printf(
        "\n--- Powers & Roots ---\n"
        "1) x^y\n"
        "2) sqrt(x)\n"
        "3) cbrt(x)\n"
        "4) Back\n"
        "Select: ");

    int choice;
    if (!read_int("", &choice)) {
      printf("Invalid selection.\n");
      continue;
    }

    if (choice == 4) {
      return;
    }

    double x, y;
    switch (choice) {
      case 1:
        if (!read_double("Enter base x: ", &x) ||
            !read_double("Enter exponent y: ", &y)) {
          printf("Invalid numbers.\n");
        } else {
          printf("%.4f ^ %.4f = %.6f\n", x, y, pow(x, y));
        }
        break;
      case 2:
        if (!read_double("Enter x: ", &x)) {
          printf("Invalid number.\n");
        } else if (x < 0) {
          printf("Cannot sqrt negative.\n");
        } else {
          printf("sqrt(%.4f) = %.6f\n", x, sqrt(x));
        }
        break;
      case 3:
        if (!read_double("Enter x: ", &x)) {
          printf("Invalid number.\n");
        } else {
          printf("cbrt(%.4f) = %.6f\n", x, cbrt(x));
        }
        break;
      default:
        printf("Invalid selection.\n");
    }
  }
}

static void handle_factorial(void) {
  printf("\n--- Factorial ---\n");
  int n;
  if (!read_int("Enter n (0–20): ", &n)) {
    printf("Invalid integer.\n");
    return;
  }
  if (n < 0 || n > MAX_FACTORIAL_INPUT) {
    printf("n must be between 0 and %d.\n", MAX_FACTORIAL_INPUT);
  } else {
    uint64_t f = factorial(n);
    printf("%d! = %" PRIu64 "\n", n, f);
  }
}

static void handle_combinatorics(void) {
  while (1) {
    printf(
        "\n--- Combinatorics ---\n"
        "1) nCr (combinations)\n"
        "2) nPr (permutations)\n"
        "3) Back\n"
        "Select: ");

    int choice;
    if (!read_int("", &choice)) {
      printf("Invalid selection.\n");
      continue;
    }
    if (choice == 3) {
      return;
    }

    int n, r;
    if (!read_int("Enter n: ", &n) || !read_int("Enter r: ", &r)) {
      printf("Invalid integers.\n");
      continue;
    }
    if (n < 0 || r < 0 || r > n) {
      printf("Require 0 <= r <= n.\n");
      continue;
    }

    if (choice == 1) {
      uint64_t c = combinations(n, r);
      if (c == 0) {
        printf("Result overflow or invalid.\n");
      } else {
        printf("C(%d, %d) = %" PRIu64 "\n", n, r, c);
      }
    } else if (choice == 2) {
      uint64_t p = permutations(n, r);
      printf("P(%d, %d) = %" PRIu64 "\n", n, r, p);
    } else {
      printf("Invalid selection.\n");
    }
  }
}

/* ======================== Main Loop ======================== */

static bool run(void) {
  printf(
      "\n=== Math Toolkit ===\n"
      "1) Trigonometry\n"
      "2) Exponential & Log\n"
      "3) Powers & Roots\n"
      "4) Factorial\n"
      "5) Combinatorics\n"
      "6) Exit\n"
      "Select: ");

  int choice;
  if (!read_int("", &choice)) {
    printf("Invalid selection.\n");
    return true;
  }

  switch (choice) {
    case 1:
      handle_trigonometry();
      break;
    case 2:
      handle_exponential();
      break;
    case 3:
      handle_powers();
      break;
    case 4:
      handle_factorial();
      break;
    case 5:
      handle_combinatorics();
      break;
    case 6:
      return false;
    default:
      printf("Invalid selection.\n");
  }
  return true;
}

int main(void) {
  while (run()) {}
  printf("Goodbye!\n");
  return EXIT_SUCCESS;
}
