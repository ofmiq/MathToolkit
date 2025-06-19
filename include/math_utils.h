#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Computes the factorial of a non-negative integer.
 * Returns 0 if the input is negative or exceeds MAX_FACTORIAL_INPUT.
 * @param n The integer whose factorial is to be computed.
 * @return The factorial of n, or 0 on invalid input.
 */
uint64_t factorial(int n);

/**
 * @brief Computes the number of permutations.
 * @param n The total number of elements.
 * @param r The number of elements to arrange.
 * @return The number of permutations, or 0 on invalid input.
 */
uint64_t permutations(int n, int r);

/**
 * @brief Computes the number of combinations.
 * @param n The total number of elements.
 * @param r The number of elements to choose.
 * @return The number of combinations, or 0 on invalid input or overflow.
 */
uint64_t combinations(int n, int r);

/**
 * @brief Safely performs multiplication and division to prevent uint64_t
 overflow.

 * @param acc Pointer to accumulator variable.
 * @param mul Multiplicand.
 * @param div Divisor.
 * @return true if the operation was successful, false if result overflows.
 */
bool safe_mul_div(uint64_t *acc, uint64_t mul, uint64_t div);

#endif
