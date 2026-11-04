*This project has been created as part of the 42 curriculum by malquran.*

# ft_printf — Recreating the C printf Function

## Description

**ft_printf** is a C programming project developed as part of the 42 curriculum. The goal is to recreate a simplified version of the standard C library function `printf()`.

The original `printf()` function allows programmers to print formatted output using different conversion specifiers. In this project, the same basic functionality is implemented from scratch using variadic functions, character printing, number conversion, and pointer manipulation.

The project helps develop a deeper understanding of:

- **Variadic functions:** Handling a variable number of arguments using `va_list`, `va_start`, `va_arg`, and `va_end`.
- **Format string parsing:** Reading a string character by character and identifying conversion specifiers.
- **Number conversion:** Converting signed and unsigned integers into decimal and hexadecimal representations.
- **Pointers and memory addresses:** Understanding pointer casting and hexadecimal address representation.
- **Recursion:** Printing numerical values by recursively processing their digits.
- **Modular programming:** Separating the main function, format dispatcher, and printing helpers.
- **Static libraries:** Compiling multiple C source files into a reusable library.
- **42 Norm:** Writing C code that follows the coding standards required by 42.

The project produces a static library named `libftprintf.a`, containing the custom `ft_printf()` implementation.

Unlike the original `printf()`, this implementation focuses on the mandatory conversion specifiers required by the 42 subject.

---

## Supported Format Specifiers

The implementation supports the following conversions:

| Specifier | Description | Example |
|---|---|---|
| `%c` | Prints a single character | `A` |
| `%s` | Prints a string | `Hello` |
| `%p` | Prints a pointer address in hexadecimal | `0x7ffe1234` |
| `%d` | Prints a signed decimal integer | `-42` |
| `%i` | Prints a signed integer | `42` |
| `%u` | Prints an unsigned decimal integer | `4294967295` |
| `%x` | Prints hexadecimal using lowercase letters | `ff` |
| `%X` | Prints hexadecimal using uppercase letters | `FF` |
| `%%` | Prints a literal percent sign | `%` |

The implementation does not include optional formatting features such as field width, precision, or formatting flags.

---

## Detailed Description

### 1. Project Structure

The implementation is divided into three main components.

**Main Function — `ft_printf()`**

The main function is responsible for reading the format string, identifying format specifiers, managing the variadic argument list, and counting printed characters.

**Format Dispatcher — `ft_format()`**

The dispatcher receives a conversion specifier and selects the appropriate printing function.

**Printing Helpers**

These functions handle the actual output of characters, strings, numbers, hexadecimal values, and pointer addresses.

This separation keeps the implementation modular and avoids unnecessary repetition.

### 2. Printing Functions

| Function | Purpose |
|---|---|
| `ft_printf` | Main function responsible for parsing the format string and managing arguments |
| `ft_format` | Selects the appropriate helper based on the format specifier |
| `ft_putchar` | Prints a single character using `write()` |
| `ft_putstr` | Prints a string character by character |
| `ft_putnbr` | Prints a signed decimal integer |
| `ft_putunsigned` | Prints an unsigned decimal integer |
| `ft_puthex` | Converts and prints hexadecimal numbers |
| `ft_putptr` | Prints a memory address in hexadecimal notation |

The printing helpers return the number of characters they print, allowing the main function to calculate the total output length.

### 3. Variadic Functions

One of the main challenges of this project is handling a variable number of arguments.

Unlike ordinary C functions, `ft_printf()` can receive different numbers and types of arguments.

For example:

```c
ft_printf("Name: %s, Age: %d", "Mothana", 21);
```

The function receives a format string followed by two additional arguments.

The `<stdarg.h>` library provides the tools needed to access these arguments.

| Macro / Type | Purpose |
|---|---|
| `va_list` | Holds the state needed to access variadic arguments |
| `va_start` | Initializes access to the additional arguments |
| `va_arg` | Retrieves the next argument using a specified type |
| `va_end` | Ends access to the argument list |

The format specifier determines the type requested through `va_arg`.

For example, `%d` requires an `int`, while `%s` requires a `char *`.

Arguments are retrieved in the order they appear in the function call.

---

## Algorithm and Data Structure

### 1. Main Algorithm

The main algorithm uses **sequential format-string parsing**.

Instead of interpreting the entire string at once, the function examines one character at a time.

The process follows these steps:

1. Initialize a character index and an output counter.
2. Initialize the variadic argument list using `va_start`.
3. Read the format string from left to right.
4. If the current character is not `%`, print it using `ft_putchar`.
5. If the current character is `%`, move to the following character to identify the conversion specifier.
6. Pass the specifier and argument list to `ft_format`.
7. The dispatcher retrieves the appropriate argument and calls its printing helper.
8. Add the number of printed characters to the main counter.
9. Continue until the end of the format string.
10. Call `va_end` and return the total character count.

### 2. Algorithm Example

Consider the following call:

```c
ft_printf("Age: %d!", 21);
```

The format string contains ordinary characters and one conversion specifier.

**Step 1 — Read ordinary characters**

The function encounters `A`, `g`, `e`, `:`, and a space.

Each character is printed directly.

Output so far:

```text
Age:
```

The output counter is now `5`.

**Step 2 — Detect the conversion specifier**

The function encounters `%`.

It moves to the next character, `d`, and calls the format dispatcher.

**Step 3 — Retrieve and print the argument**

The dispatcher recognizes `d` as a signed decimal conversion.

It retrieves the integer `21` and passes it to `ft_putnbr`.

The helper prints:

```text
21
```

It returns `2` because two characters were printed.

**Step 4 — Update the counter**

The main function adds `2` to the previous count of `5`.

The counter becomes `7`.

**Step 5 — Continue parsing**

The function prints the final character, `!`.

Final output:

```text
Age: 21!
```

Final return value:

```text
8
```

This demonstrates why the function must distinguish between the position in the original format string and the number of characters actually printed.

### 3. Number Conversion Algorithm

Signed integers, unsigned integers, and hexadecimal values are printed using **recursive digit extraction**.

For decimal numbers, the algorithm uses:

- Division by `10` to process the preceding digits.
- Modulo `10` to extract the final digit.
- Character conversion to obtain the ASCII representation.

For hexadecimal numbers, the same principle is applied using base `16`.

The hexadecimal helper selects one of two character sets:

```text
0123456789abcdef
```

or:

```text
0123456789ABCDEF
```

The selected character set depends on whether the format specifier is `%x` or `%X`.

This makes it possible to reuse the same conversion algorithm for lowercase and uppercase hexadecimal output.

### 4. Pointer Representation

The `%p` specifier requires printing a memory address in hexadecimal notation.

The implementation follows these steps:

1. Receive a pointer as `void *`.
2. Convert the pointer to an unsigned integer type capable of holding the address on the target platform.
3. Print the hexadecimal prefix `0x`.
4. Reuse the hexadecimal printing function to display the address.

The implementation uses `unsigned long` for pointer-address conversion on the target 64-bit Linux environment.

For a NULL pointer, the implementation prints:

```text
(nil)
```

This follows the representation used by the target Linux `printf()` implementation.

### 5. Data Structures

The project does not require complex data structures such as linked lists, trees, or dynamically allocated arrays.

Instead, it relies on a small number of basic C types:

| Data Type | Purpose |
|---|---|
| `const char *` | Stores the format string |
| `va_list` | Maintains access to variadic arguments |
| `int` | Stores character indexes and output counts |
| `unsigned int` | Represents unsigned numerical arguments |
| `unsigned long` | Represents hexadecimal values and pointer addresses |
| `char *` | References strings and hexadecimal digit tables |

No additional heap-based data structure is required by the chosen algorithm.

### 6. Design Justification

The implementation uses a **modular dispatcher-based design** for several reasons.

**Separation of responsibilities**

The main function handles parsing, the dispatcher handles conversion selection, and the helpers handle printing.

This makes individual components easier to understand and test.

**Code reusability**

The hexadecimal conversion function is shared between `%x`, `%X`, and pointer printing.

This avoids implementing the same base-conversion algorithm multiple times.

**Recursion**

Recursive numerical conversion allows digits to be printed in the correct order without allocating temporary buffers.

**Minimal memory usage**

The implementation does not require dynamic memory allocation for its formatting operations.

**Maintainability**

Dividing functionality into smaller helpers reduces code duplication and makes debugging easier.

### 7. Time and Space Complexity

For a format string of length `n`, parsing the string requires a single left-to-right traversal.

Each numerical conversion additionally processes the digits of its corresponding argument.

The overall time complexity is proportional to the number of characters examined and produced.

**Time complexity:** `O(n + k)`

Where:

- `n` is the length of the format string.
- `k` is the total number of digits processed by numerical conversions.

**Auxiliary space complexity:** `O(d)`

Where `d` is the maximum recursion depth required to print a numerical argument.

The main parsing loop itself uses constant auxiliary space, while recursive number conversion uses stack space proportional to the number of digits.

---

## Instructions

### 1. Compilation

The project uses a Makefile to compile the source files and create the static library.

From the root of the repository, run:

```bash
make
```

This builds:

```text
libftprintf.a
```

The Makefile supports the standard targets:

```bash
make          # Compile the library
make all      # Compile the library
make clean    # Remove object files
make fclean   # Remove object files and the library
make re       # Rebuild the library from scratch
```

The project is compiled using:

```bash
cc -Wall -Wextra -Werror
```

These flags enable compiler warnings and treat warnings as errors.

### 2. Using ft_printf

Include the project header in a C source file:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello, %s!\n", "42");
	ft_printf("Number: %d\n", 42);
	ft_printf("Hexadecimal: %x\n", 255);
	return (0);
}
```

Compile the test program by linking it with the generated library:

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o test_printf
```

Execute the program:

```bash
./test_printf
```

Expected output:

```text
Hello, 42!
Number: 42
Hexadecimal: ff
```

### 3. Norminette

The project follows the coding standards of the 42 curriculum.

To check the source files and header:

```bash
norminette
```

Norminette checks aspects such as indentation, spacing, function length, variable declarations, and naming conventions.

---

## Resources

### Official Documentation

**42 ft_printf Subject**

The official 42 project subject is the primary reference for the mandatory requirements, supported conversions, permitted functions, and expected behavior.

**C Standard Library Documentation**

- [printf(3) — Linux Manual](https://man7.org/linux/man-pages/man3/printf.3.html) — Describes formatted output, conversion specifiers, and return values.
- [stdarg(3) — Linux Manual](https://man7.org/linux/man-pages/man3/stdarg.3.html) — Explains variadic argument handling using `va_list`, `va_start`, `va_arg`, and `va_end`.
- [write(2) — Linux Manual](https://man7.org/linux/man-pages/man2/write.2.html) — Documents the `write()` system call and its return values.
- [cppreference — C Language](https://en.cppreference.com/w/c.html) — Reference material for C syntax, data types, and language behavior.

### Algorithms and Number Conversion

- [GeeksforGeeks — Recursion in C](https://www.geeksforgeeks.org/c/recursion-in-c/) — Introduces recursion and explains recursive function calls.
- [GeeksforGeeks — Decimal to Hexadecimal Conversion](https://www.geeksforgeeks.org/dsa/program-decimal-hexadecimal-conversion/) — Explains hexadecimal number representation and base conversion.

### Compilation and Development

- [GNU Make Manual](https://www.gnu.org/software/make/manual/make.html) — Reference for Makefiles, build targets, and dependencies.
- [GCC Documentation](https://gcc.gnu.org/onlinedocs/) — Documentation for compilation options and compiler warnings.
- [42 Norminette](https://github.com/42School/norminette) — The official 42 tool for checking coding-style compliance.

### AI Usage

AI tools were used as educational assistance during the development of this project.

The assistance included:

- Explaining C variadic functions and how `va_list`, `va_start`, `va_arg`, and `va_end` work.
- Clarifying the relationship between the main `ft_printf` function, the format dispatcher, and the printing helpers.
- Helping explain recursive number conversion and hexadecimal representation.
- Recommending documentation and learning resources.

The implementation was developed through hands-on programming and an iterative learning process, with AI used to support understanding.

---

## Author

**malquran**

42 Network — ft_printf Project