# char-utils

<versionBadge>![Version 0.6.0](https://img.shields.io/badge/version-0.6.0-blue.svg)</versionBadge>
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CI/CD Status Badge](https://github.com/mofosyne/char-utils/actions/workflows/ci.yml/badge.svg)](https://github.com/mofosyne/char-utils/actions)

**Pull Requests and Contributions are Welcomed**

Small C utility library macros and functions for char handling.
e.g. conversion or checks for hex, digits and ascii values

You are encourage to copy and paste snippets as you need in your project,
but you can install it as a normal C header file as well!

Note that some of these macro already have a C standard library equvalent,
so you are encourage to use C standard library function for portability.

## Usage

The library consists of one header file, easily integrated into your project manually or via [clib](https://github.com/clibs/clib)

```bash
clib install mofosyne/char-utils.h
```

or copy these files manually to your source folder:

```bash
char-utils.h
```

## Examples

```c
#include "char-utils.h"

/* Character type checks */
if (IS_DIGIT(c))   { /* '0'-'9' */ }
if (IS_HEX_DIGIT(c)) { /* '0'-'9', 'a'-'f', 'A'-'F' */ }
if (IS_ALPHA(c))   { /* 'a'-'z', 'A'-'Z' */ }
if (IS_SPACE(c))   { /* ' ', '\t', '\n', '\r', '\f', '\v' */ }

/* Conversions */
int digit = ASCII_TO_DIGIT(c, -1);       /* '7' -> 7, invalid -> -1 */
int hex   = HEX_TO_INT(c, -1);           /* 'F' -> 15, invalid -> -1 */
char upper = TO_UPPER(c);                /* 'a' -> 'A', non-alpha unchanged */
char lo_hex = NIBBLE_TO_LOWERCASE_HEX(n, '?'); /* 10 -> 'a' */

/* Nibble splitting */
uint8_t hi = HIGH_NIBBLE(byte);          /* 0xAB -> 0xA */
uint8_t lo = LOW_NIBBLE(byte);           /* 0xAB -> 0xB */

/* ASCII diagnostics (safe with getchar() return value) */
int c = getchar();
printf("%s\n", ascii_to_diagnostics(c, "[EOF]")); /* prints e.g. "[LF]" or "A" */
```

## API

Each safe macro accepts an explicit `DEFAULT` value returned on invalid input.
`FAST_` variants skip validation and are suitable when input is already known-good.

### Character Type Checks

| Macro | Equivalent | Description |
|---|---|---|
| `IS_BINARY(ch)` | — | `'0'` or `'1'` |
| `IS_OCTAL(ch)` | — | `'0'`–`'7'` |
| `IS_DIGIT(ch)` | `isdigit()` | `'0'`–`'9'` |
| `IS_LOWER(ch)` | `islower()` | `'a'`–`'z'` |
| `IS_UPPER(ch)` | `isupper()` | `'A'`–`'Z'` |
| `IS_ALPHA(ch)` | `isalpha()` | `'a'`–`'z'`, `'A'`–`'Z'` |
| `IS_ALNUM(ch)` | `isalnum()` | alphanumeric |
| `IS_HEX_DIGIT(ch)` | `isxdigit()` | `'0'`–`'9'`, `'a'`–`'f'`, `'A'`–`'F'` |
| `IS_PRINTABLE(ch)` | `isprint()` | `' '`–`'~'` |
| `IS_SPACE(ch)` | `isspace()` | whitespace (C locale) |
| `IS_PUNCT(ch)` | `ispunct()` | printable, non-alnum, non-space |
| `IS_BRACKET(ch)` | — | `(`, `)`, `[`, `]`, `{`, `}` |
| `IS_SYMBOL(ch)` | — | printable punct, non-bracket |
| `IS_ASCII(ch)` | — | `0`–`127` |
| `IS_EXTENDED_ASCII(ch)` | — | `0`–`255` |

Each has a `_GROKKABLE` variant with explicit range comparisons for readability.

### Case Conversion

| Macro | Description |
|---|---|
| `TO_UPPER(ch)` | Lower to upper, non-alpha unchanged |
| `TO_LOWER(ch)` | Upper to lower, non-alpha unchanged |
| `TOGGLE_CASE(ch)` | Flip case, non-alpha unchanged |
| `FAST_TO_UPPER(ch)` | Bit-clear, no guard |
| `FAST_TO_LOWER(ch)` | Bit-set, no guard |
| `FAST_TOGGLE_CASE(ch)` | Bit-flip, no guard |

### Digit & Hex Conversion

| Macro | Description |
|---|---|
| `ASCII_TO_DIGIT(ch, DEFAULT)` | `'0'`–`'9'` → 0–9 |
| `DIGIT_TO_ASCII(n, DEFAULT)` | 0–9 → `'0'`–`'9'` |
| `ASCII_TO_BINARY(ch, DEFAULT)` | `'0'`/`'1'` → 0/1 |
| `ASCII_TO_OCTAL(ch, DEFAULT)` | `'0'`–`'7'` → 0–7 |
| `HEX_TO_INT(ch, DEFAULT)` | hex char → 0–15 |
| `NIBBLE_TO_UPPERCASE_HEX(n, DEFAULT)` | 0–15 → `'0'`–`'F'` |
| `NIBBLE_TO_LOWERCASE_HEX(n, DEFAULT)` | 0–15 → `'0'`–`'f'` |

`FAST_` variants available for all of the above.

### Nibble Operations

| Macro | Description |
|---|---|
| `HIGH_NIBBLE(byte)` | Upper 4 bits |
| `LOW_NIBBLE(byte)` | Lower 4 bits |

### ASCII Diagnostics

```c
const char *ascii_to_diagnostics(int ch, const char *default_str);
```

Returns a human-readable string for any byte value (e.g. `"[LF]"`, `"[NUL]"`, `"A"`).
Accepts the `int` return type of `getchar()`/`fgetc()` directly; returns `default_str` for values outside 0–255.
