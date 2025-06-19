#define _USE_MATH_DEFINES
#include "menus.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "input.h"
#include "math_utils.h"

bool run(void) {
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

void handle_trigonometry(void) {
  const double pi = PI;
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

void handle_exponential(void) {
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

void handle_powers(void) {
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

void handle_factorial(void) {
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

void handle_combinatorics(void) {
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
