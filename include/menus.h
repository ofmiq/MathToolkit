#ifndef MENUS_H
#define MENUS_H

#include <stdbool.h>

/**
 * @brief Displays the main menu and handles the user's top-level selection.
 * @return true to continue the program, false to exit.
 */
bool run(void);

/**
 * @brief Displays and manages the Trigonometry submenu.
 */
void handle_trigonometry(void);

/**
 * @brief Displays and manages the Exponential & Logarithmic submenu.
 */
void handle_exponential(void);

/**
 * @brief Displays and manages the Powers & Roots submenu.
 */
void handle_powers(void);

/**
 * @brief Prompts the user for an integer and displays its factorial.
 */
void handle_factorial(void);

/**
 * @brief Displays and manages the Combinatorics submenu.
 */
void handle_combinatorics(void);

#endif
