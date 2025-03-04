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

#define CHARUTIL_BINARY_COUNT 2
#define CHARUTIL_BINARY_COUNT_GROKKABLE (sizeof("01") - 1)
#define CHARUTIL_OCTAL_COUNT 8
#define CHARUTIL_OCTAL_COUNT_GROKKABLE (sizeof("01234567") - 1)
#define CHARUTIL_DIGIT_COUNT 10
#define CHARUTIL_DIGIT_COUNT_GROKKABLE (sizeof("0123456789") - 1)
#define CHARUTIL_HEX_COUNT 16
#define CHARUTIL_HEX_COUNT_GROKKABLE (sizeof("0123456789ABCDEF") - 1)
#define CHARUTIL_ALPHABET_COUNT 26
#define CHARUTIL_ALPHABET_COUNT_GROKKABLE (sizeof("abcdefghijklmnopqrstuvwxyz") - 1)
#define CHARUTIL_ALPHANUMERIC_COUNT 36
#define CHARUTIL_ALPHANUMERIC_COUNT_GROKKABLE (sizeof("0123456789abcdefghijklmnopqrstuvwxyz") - 1)

/* ==========================
 * Character Type Checks
 * ========================== */
#define IS_BINARY(ch) ((unsigned)((ch) - '0') < CHARUTIL_BINARY_COUNT)                                  ///< single unsigned cmp, no branches for speed.
#define IS_OCTAL(ch) ((unsigned)((ch) - '0') < CHARUTIL_OCTAL_COUNT)                                    ///< single unsigned cmp, no branches for speed.
#define IS_DIGIT(ch) ((unsigned)((ch) - '0') < CHARUTIL_DIGIT_COUNT)                                    ///< single unsigned cmp, no branches for speed. Equivalent to isdigit() from <ctype.h>
#define IS_LOWER(ch) ((unsigned)((ch) - 'a') < CHARUTIL_ALPHABET_COUNT)                                 ///< single unsigned cmp, no branches for speed. Equivalent to islower() from <ctype.h>
#define IS_UPPER(ch) ((unsigned)((ch) - 'A') < CHARUTIL_ALPHABET_COUNT)                                 ///< single unsigned cmp, no branches for speed. Equivalent to isupper() from <ctype.h>
#define IS_ALPHA(ch) (IS_LOWER(ch) || IS_UPPER(ch))                                                     ///< Equivalent to isalpha() from <ctype.h>
#define IS_ALNUM(ch) (IS_DIGIT(ch) || IS_ALPHA(ch))                                                     ///< Equivalent to isalnum() from <ctype.h>
#define IS_HEX_DIGIT(ch) (IS_DIGIT(ch) || ((unsigned)((ch) - 'A') < 6) || ((unsigned)((ch) - 'a') < 6)) ///< Equivalent to isxdigit() from <ctype.h>
#define IS_PRINTABLE(ch) ((unsigned)((ch) - 32) < 95)                                                   ///< single unsigned cmp, no branches for speed. Equivalent to isprint() from <ctype.h>

#define IS_ASCII(ch) ((unsigned)(ch) < 128)          ///< single unsigned cmp, no branches for speed.
#define IS_EXTENDED_ASCII(ch) ((unsigned)(ch) < 256) ///< single unsigned cmp, no branches for speed.

#define IS_SPACE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n' || (ch) == '\r' || (ch) == '\f' || (ch) == '\v') ///< Equivalent to isspace() from <ctype.h>
#define IS_PUNCT(ch) ((IS_PRINTABLE(ch)) && !(IS_ALNUM(ch) || IS_SPACE(ch)))                                       ///< Equivalent to ispunct() from <ctype.h>
#define IS_BRACKET(ch) ((ch) == '(' || (ch) == ')' || (ch) == '{' || (ch) == '}' || (ch) == '[' || (ch) == ']')
#define IS_SYMBOL(ch) ((IS_PUNCT(ch)) && !(IS_BRACKET(ch)))

/* Grokkable Version (Slower but more understandable. Fast if compiler optimisation is enabled) */
#define IS_BINARY_GROKKABLE(ch) ((ch) == '0' || (ch) == '1')
#define IS_OCTAL_GROKKABLE(ch) ((ch) >= '0' && (ch) <= '7')
#define IS_DIGIT_GROKKABLE(ch) ('0' <= (ch) && (ch) <= '9')                                                                     ///< Equivalent to isdigit() from <ctype.h>
#define IS_LOWER_GROKKABLE(ch) ('a' <= (ch) && (ch) <= 'z')                                                                     ///< Equivalent to islower() from <ctype.h>
#define IS_UPPER_GROKKABLE(ch) ('A' <= (ch) && (ch) <= 'Z')                                                                     ///< Equivalent to isupper() from <ctype.h>
#define IS_ALPHA_GROKKABLE(ch) (('a' <= (ch) && (ch) <= 'z') || ('A' <= (ch) && (ch) <= 'Z'))                                   ///< Equivalent to isalpha() from <ctype.h>
#define IS_ALNUM_GROKKABLE(ch) (('0' <= (ch) && (ch) <= '9') || ('a' <= (ch) && (ch) <= 'z') || ('A' <= (ch) && (ch) <= 'Z'))   ///< Equivalent to isalnum() from <ctype.h>
#define IS_HEX_DIGIT_GROKKABLE(ch) ('0' <= (ch) && (ch) <= '9') || ('a' <= (ch) && (ch) <= 'f') || ('A' <= (ch) && (ch) <= 'F') ///< Equivalent to isxdigit() from <ctype.h>
#define IS_PRINTABLE_GROKKABLE(ch) (' ' <= (ch) && (ch) <= '~')                                                                 ///< Equivalent to isprint() from <ctype.h>

/* ==========================
 * Character Case Conversion
 * ========================== */
// e.g. 'A'=0b01000001
// e.g. 'a'=0b01100001
#define TO_UPPER(ch) (IS_LOWER(ch) ? ((ch) & ~(1 << 5)) : (ch))   ///< Clear 5th bit of an ascii alphabet to set as upper case. Similar to toupper() from <ctype.h>
#define TO_LOWER(ch) (IS_UPPER(ch) ? ((ch) | (1 << 5)) : (ch))    ///< Set 5th bit of an ascii alphabet to set to lower case. Similar to tolower() from <ctype.h>
#define TOGGLE_CASE(ch) (IS_ALPHA(ch) ? ((ch) ^ (1 << 5)) : (ch)) ///< Flip 5th bit of an ascii alphabet to flip to between cases

#define FAST_TO_UPPER(ch) ((ch) & ~(1 << 5))   ///< Clear 5th bit of an ascii alphabet to set as upper case. Similar to toupper() from <ctype.h>
#define FAST_TO_LOWER(ch) ((ch) | (1 << 5))    ///< Set 5th bit of an ascii alphabet to set to lower case. Similar to tolower() from <ctype.h>
#define FAST_TOGGLE_CASE(ch) ((ch) ^ (1 << 5)) ///< Flip 5th bit of an ascii alphabet to flip to between cases

/* ==========================
 * Digit & Hex Conversions
 * ========================== */
// Dev Note: No need to over optimise this. Best to just be explicit
//           here for understandability. But provide a fast version for
//           those who really need it and are careful enough to use it.

#define ASCII_TO_BINARY(ch, DEFAULT) (((ch) == '0' || (ch) == '1') ? ((ch) - '0') : DEFAULT) ///< Similar to strtol() from <ctype.h>
#define BINARY_TO_ASCII(num, DEFAULT) ((unsigned)(num) < 2 ? ((num) + '0') : DEFAULT)
#define FAST_ASCII_TO_BINARY(ch) ((ch) - '0')
#define FAST_BINARY_TO_ASCII(num) ((num) + '0')

#define ASCII_TO_OCTAL(ch, DEFAULT) (('0' <= (ch) && (ch) <= '7') ? ((ch) - '0') : DEFAULT) ///< Similar to strtol() from <ctype.h>
#define OCTAL_TO_ASCII(num, DEFAULT) ((unsigned)(num) < 8 ? ((num) + '0') : DEFAULT)
#define FAST_ASCII_TO_OCTAL(ch) ((ch) - '0')
#define FAST_OCTAL_TO_ASCII(num) ((num) + '0')

#define ASCII_TO_DIGIT(ch) (('0' <= (ch) && (ch) <= '9') ? ((ch) - '0') : -1) ///< Similar to strtol() from <ctype.h>
#define DIGIT_TO_ASCII(num, DEFAULT) ((unsigned)(num) < 10 ? ((num) + '0') : DEFAULT)
#define FAST_DIGIT_TO_ASCII(num) ((num) + '0')
#define FAST_ASCII_TO_DIGIT(ch) ((ch) - '0')

#define HEX_TO_INT(ch, DEFAULT) (('0' <= (ch) && (ch) <= '9') ? ((ch) - '0') : (((ch) >= 'A' && (ch) <= 'F') ? ((ch) - 'A' + 10) : (((ch) >= 'a' && (ch) <= 'f') ? ((ch) - 'a' + 10) : DEFAULT)))
#define FAST_UPPERCASE_HEX_TO_INT(ch) (('0' <= (ch) && (ch) <= '9') ? ((ch) - '0') : ((ch) - 'A' + 10))
#define FAST_LOWERCASE_HEX_TO_INT(ch) (('0' <= (ch) && (ch) <= '9') ? ((ch) - '0') : ((ch) - 'a' + 10))

#define NIBBLE_TO_UPPERCASE_HEX(n, DEFAULT) ((unsigned)(n) < 16 ? ((n) < 10 ? ((n) + '0') : ((n) - 10 + 'A')) : DEFAULT)
#define NIBBLE_TO_LOWERCASE_HEX(n, DEFAULT) ((unsigned)(n) < 16 ? ((n) < 10 ? ((n) + '0') : ((n) - 10 + 'a')) : DEFAULT)
#define FAST_NIBBLE_TO_UPPERCASE_HEX(n) ((n) < 10 ? ((n) + '0') : ((n) - 10 + 'A'))
#define FAST_NIBBLE_TO_LOWERCASE_HEX(n) ((n) < 10 ? ((n) + '0') : ((n) - 10 + 'a'))

/* ==========================
 * Bitwise Operations
 * ========================== */
#define HIGH_NIBBLE(byte) (((byte) >> 4) & 0xF)
#define LOW_NIBBLE(byte) ((byte) & 0xF)

/* ==========================
 * ASCII Diagnostic
 * ========================== */
static inline const char *ascii_to_diagnostics(unsigned char ch)
{
    static const char *ascii_lut[256] = {
        "[NUL]",  "[SOH]",  "[STX]",  "[ETX]",  "[EOT]",  "[ENQ]",  "[ACK]",  "[BEL]",  "[BS]",   "[TAB]",  "[LF]",   "[VT]",   "[FF]",   "[CR]",   "[SO]",   "[SI]",   "[DLE]",  "[DC1]",  "[DC2]",
        "[DC3]",  "[DC4]",  "[NAK]",  "[SYN]",  "[ETB]",  "[CAN]",  "[EM]",   "[SUB]",  "[ESC]",  "[FS]",   "[GS]",   "[RS]",   "[US]",   " ",      "!",      "\"",     "#",      "$",      "%",
        "&",      "'",      "(",      ")",      "*",      "+",      ",",      "-",      ".",      "/",      "0",      "1",      "2",      "3",      "4",      "5",      "6",      "7",      "8",
        "9",      ":",      ";",      "<",      "=",      ">",      "?",      "@",      "A",      "B",      "C",      "D",      "E",      "F",      "G",      "H",      "I",      "J",      "K",
        "L",      "M",      "N",      "O",      "P",      "Q",      "R",      "S",      "T",      "U",      "V",      "W",      "X",      "Y",      "Z",      "[",      "\\",     "]",      "^",
        "_",      "`",      "a",      "b",      "c",      "d",      "e",      "f",      "g",      "h",      "i",      "j",      "k",      "l",      "m",      "n",      "o",      "p",      "q",
        "r",      "s",      "t",      "u",      "v",      "w",      "x",      "y",      "z",      "{",      "|",      "}",      "~",      "[DEL]",  "[0x80]", "[0x81]", "[0x82]", "[0x83]", "[0x84]",
        "[0x85]", "[0x86]", "[0x87]", "[0x88]", "[0x89]", "[0x8A]", "[0x8B]", "[0x8C]", "[0x8D]", "[0x8E]", "[0x8F]", "[0x90]", "[0x91]", "[0x92]", "[0x93]", "[0x94]", "[0x95]", "[0x96]", "[0x97]",
        "[0x98]", "[0x99]", "[0x9A]", "[0x9B]", "[0x9C]", "[0x9D]", "[0x9E]", "[0x9F]", "[0xA0]", "[0xA1]", "[0xA2]", "[0xA3]", "[0xA4]", "[0xA5]", "[0xA6]", "[0xA7]", "[0xA8]", "[0xA9]", "[0xAA]",
        "[0xAB]", "[0xAC]", "[0xAD]", "[0xAE]", "[0xAF]", "[0xB0]", "[0xB1]", "[0xB2]", "[0xB3]", "[0xB4]", "[0xB5]", "[0xB6]", "[0xB7]", "[0xB8]", "[0xB9]", "[0xBA]", "[0xBB]", "[0xBC]", "[0xBD]",
        "[0xBE]", "[0xBF]", "[0xC0]", "[0xC1]", "[0xC2]", "[0xC3]", "[0xC4]", "[0xC5]", "[0xC6]", "[0xC7]", "[0xC8]", "[0xC9]", "[0xCA]", "[0xCB]", "[0xCC]", "[0xCD]", "[0xCE]", "[0xCF]", "[0xD0]",
        "[0xD1]", "[0xD2]", "[0xD3]", "[0xD4]", "[0xD5]", "[0xD6]", "[0xD7]", "[0xD8]", "[0xD9]", "[0xDA]", "[0xDB]", "[0xDC]", "[0xDD]", "[0xDE]", "[0xDF]", "[0xE0]", "[0xE1]", "[0xE2]", "[0xE3]",
        "[0xE4]", "[0xE5]", "[0xE6]", "[0xE7]", "[0xE8]", "[0xE9]", "[0xEA]", "[0xEB]", "[0xEC]", "[0xED]", "[0xEE]", "[0xEF]", "[0xF0]", "[0xF1]", "[0xF2]", "[0xF3]", "[0xF4]", "[0xF5]", "[0xF6]",
        "[0xF7]", "[0xF8]", "[0xF9]", "[0xFA]", "[0xFB]", "[0xFC]", "[0xFD]", "[0xFE]", "[0xFF]"};
    return ascii_lut[ch];
}

#endif // CHAR_UTILS_H
