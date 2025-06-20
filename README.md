# Math Toolkit

A command-line C application for performing common mathematical operations, including:

- Trigonometric functions
- Exponential and logarithmic functions
- Power and root operations
- Factorial calculation
- Combinatorics
- Planimetrics

## Requirements

- A C compiler (e.g., `gcc`, `clang`)
- Make utility

## Compile

Just run:

```bash
make
````

This will compile the project using the `Makefile` and create an executable called:

```bash
math_toolkit
```

To clean up object files and the binary:

```bash
make clean
```

## Usage

After compiling, launch the toolkit:

```bash
./math_toolkit
```

You'll see an interactive menu like:

```
=== Math Toolkit ===
1. Trigonometry
2. Exponential & Log
3. Powers & Roots
4. Factorial
5. Combinatorics
6. Planimetrics
7. Exit
```

Navigate through the submenus and input values as prompted.

## License

This project is released under the MIT License. See [LICENSE](https://github.com/ofmiq/MathToolkit/blob/main/LICENSE) for details.