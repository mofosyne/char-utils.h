/*
    Char Utility Macros
    Author: Brian Khuu (2025)

    # MIT License

    Copyright (c) 2025 Brian Khuu

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

 */
#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

/* Design Notes:
 * The below macros are focused on being compact even if optimisation is
 * disabled by relying only on arithmic operation and comparison, rather
 * than the more computationally expensive branching instructions.
 *
 * In addition there are some macros with a grokkable version included
 * with the same behavior but with clearer syntax. They will still
 * compile to the same size if optimisation is enabled. In practice for
 * many projects, especially in embedded compilers, optimisation may be
 * unused due to being locked behind a paywall or being hard to use
 * without hitting compiler optimisation bugs...
 *
 * */

/* ==========================
 * Set Sizes
 * ========================== */
#define CHARUTIL_DIGIT_COUNT 10
#define CHARUTIL_DIGIT_COUNT_GROKKABLE (sizeof("0123456789") - 1)
#define CHARUTIL_ALPHABET_COUNT 26
#define CHARUTIL_ALPHABET_COUNT_GROKKABLE (sizeof("abcdefghijklmnopqrstuvwxyz") - 1)
#define CHARUTIL_ALPHANUMERIC_COUNT 36
#define CHARUTIL_ALPHANUMERIC_COUNT_GROKKABLE (sizeof("0123456789abcdefghijklmnopqrstuvwxyz") - 1)

/* ==========================
 * Fast Character Type Checks
 * ========================== */
#define IS_DIGIT(ch) ((unsigned)((ch) - '0') < CHARUTIL_DIGIT_COUNT)
#define IS_LOWER(ch) ((unsigned)((ch) - 'a') < CHARUTIL_ALPHABET_COUNT)
#define IS_UPPER(ch) ((unsigned)((ch) - 'A') < CHARUTIL_ALPHABET_COUNT)
#define IS_ALPHA(ch) (IS_LOWER(ch) || IS_UPPER(ch))
#define IS_ALNUM(ch) (IS_DIGIT(ch) || IS_ALPHA(ch))
#define IS_HEX_DIGIT(ch) (IS_DIGIT(ch) || ((unsigned)((ch) - 'A') < 6) || ((unsigned)((ch) - 'a') < 6))
#define IS_SPACE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n' || (ch) == '\r' || (ch) == '\f' || (ch) == '\v')
#define IS_PRINTABLE(ch) ((unsigned)((ch) - 32) < 95)
#define IS_ASCII(ch) ((unsigned)(ch) < 128)
#define IS_EXTENDED_ASCII(ch) ((unsigned)(ch) < 256)

/* Grokkable Version (Slower but more understandable. Fast if compiler optimisation is enabled) */
#define IS_DIGIT_GROKKABLE(ch) ('0' <= (ch) && (ch) <= '9')
#define IS_LOWER_GROKKABLE(ch) ('a' <= (ch) && (ch) <= 'z')
#define IS_UPPER_GROKKABLE(ch) ('A' <= (ch) && (ch) <= 'Z')
#define IS_ALPHA_GROKKABLE(ch) (('a' <= (ch) && (ch) <= 'z') || ('A' <= (ch) && (ch) <= 'Z'))
#define IS_ALNUM_GROKKABLE(ch) (('0' <= (ch) && (ch) <= '9') || ('a' <= (ch) && (ch) <= 'z') || ('A' <= (ch) && (ch) <= 'Z'))
#define IS_HEX_DIGIT_GROKKABLE(ch) ('0' <= (ch) && (ch) <= '9') || ('a' <= (ch) && (ch) <= 'f') || ('A' <= (ch) && (ch) <= 'F')
#define IS_SPACE_GROKKABLE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n' || (ch) == '\r' || (ch) == '\f' || (ch) == '\v')
#define IS_PRINTABLE_GROKKABLE(ch) (' ' <= (ch) && (ch) <= '~')
#define IS_ASCII_GROKKABLE(ch) ((unsigned)(ch) < (1 << 7))
#define IS_EXTENDED_ASCII_GROKKABLE(ch) ((unsigned)(ch) < (1 << 8))

/* ==========================
 * Fast Character Case Conversion
 * ========================== */
// e.g. 'A'=0b01000001
// e.g. 'a'=0b01100001
#define TO_UPPER(ch) ((ch) & ~(1 << 5))   ///< Clear 5th bit of an ascii alphabet to set as upper case
#define TO_LOWER(ch) ((ch) | (1 << 5))    ///< Set 5th bit of an ascii alphabet to set to lower case
#define TOGGLE_CASE(ch) ((ch) ^ (1 << 5)) ///< Flip 5th bit of an ascii alphabet to flip to between cases

/* Slightly safer implemention of case conversion. At least check that it's actually an alphabet character. */
#define SAFE_TO_UPPER(ch) (IS_LOWER(ch) ? TO_UPPER(ch) : (ch))
#define SAFE_TO_LOWER(ch) (IS_UPPER(ch) ? TO_LOWER(ch) : (ch))
#define SAFE_TOGGLE_CASE(ch) (IS_ALPHA(ch) ? TOGGLE_CASE(ch) : (ch))

/* ==========================
 * Fast Digit & Hex Conversions
 * ========================== */
#define DIGIT_TO_ASCII(num) ((num) + '0')
#define ASCII_TO_DIGIT(ch) ((ch) - '0')
#define HEX_TO_INT(ch) (IS_DIGIT(ch) ? ((ch) - '0') : (((ch) | 0x20) - 'a' + 10))
#define NIBBLE_TO_HEX(n) ((n) < 10 ? ((n) + '0') : ((n) - 10 + 'A'))
#define NIBBLE_TO_HEX_UPPER(n) ((n) < 10 ? ((n) + '0') : ((n) - 10 + 'A'))
#define NIBBLE_TO_HEX_LOWER(n) ((n) < 10 ? ((n) + '0') : ((n) - 10 + 'a'))

/* Slightly safer implemention of digit/hex conversion. Check that we are actually dealing with digit or hex */
// Depreciation Consideration Warning: https://github.com/mofosyne/char-utils.h/issues/1
#define SAFE_DIGIT_TO_ASCII(num) ((unsigned)(num) < 10 ? DIGIT_TO_ASCII(num) : '\0')
#define SAFE_ASCII_TO_DIGIT(ch) (IS_DIGIT(ch) ? ASCII_TO_DIGIT(ch) : -1)
#define SAFE_HEX_TO_INT(ch) (IS_DIGIT(ch) ? ((ch) - '0') : (((ch) >= 'A' && (ch) <= 'F') ? ((ch) - 'A' + 10) : (((ch) >= 'a' && (ch) <= 'f') ? ((ch) - 'a' + 10) : -1)))
#define SAFE_NIBBLE_TO_HEX(n) ((unsigned)(n) < 16 ? NIBBLE_TO_HEX(n) : '\0')
#define SAFE_NIBBLE_TO_HEX_UPPER(n) ((unsigned)(n) < 16 ? NIBBLE_TO_HEX_UPPER(n) : '\0')
#define SAFE_NIBBLE_TO_HEX_LOWER(n) ((unsigned)(n) < 16 ? NIBBLE_TO_HEX_LOWER(n) : '\0')

/* ==========================
 * Bitwise Operations
 * ========================== */
#define HIGH_NIBBLE(byte) (((byte) >> 4) & 0xF)
#define LOW_NIBBLE(byte) ((byte) & 0xF)

#endif // CHAR_UTILS_H
