#include "char-utils.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static_assert(CHARUTIL_BINARY_COUNT == CHARUTIL_BINARY_COUNT_GROKKABLE);
static_assert(CHARUTIL_OCTAL_COUNT == CHARUTIL_OCTAL_COUNT_GROKKABLE);
static_assert(CHARUTIL_DIGIT_COUNT == CHARUTIL_DIGIT_COUNT_GROKKABLE);
static_assert(CHARUTIL_ALPHABET_COUNT == CHARUTIL_ALPHABET_COUNT_GROKKABLE);
static_assert(CHARUTIL_ALPHANUMERIC_COUNT == CHARUTIL_ALPHANUMERIC_COUNT_GROKKABLE);

bool check_if_character_is_accepted(unsigned ch, const char *accept, unsigned accept_count)
{
    for (int i = 0; i < accept_count; i++)
    {
        if (ch == accept[i])
        {
            return true;
        }
    }
    return false;
}

void test_character_checks(void)
{
    // Test basic checks

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "01";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_BINARY(ch) == accepted);
        assert(IS_BINARY_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "01234567";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_OCTAL(ch) == accepted);
        assert(IS_OCTAL_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "0123456789";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_DIGIT(ch) == accepted);
        assert(IS_DIGIT_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "abcdefghijklmnopqrstuvwxyz";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_LOWER(ch) == accepted);
        assert(IS_LOWER_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_UPPER(ch) == accepted);
        assert(IS_UPPER_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_ALPHA(ch) == accepted);
        assert(IS_ALPHA_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_ALNUM(ch) == accepted);
        assert(IS_ALNUM_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "0123456789ABCDEFabcdef";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_HEX_DIGIT(ch) == accepted);
        assert(IS_HEX_DIGIT_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}:\"<>?[];',./\\ -=`|~";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_PRINTABLE(ch) == accepted);
        assert(IS_PRINTABLE_GROKKABLE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        assert(IS_ASCII(ch) == ((0 <= ch) && (ch < 128)));
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        assert(IS_EXTENDED_ASCII(ch) == ((0 <= ch) && (ch < 256)));
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = " \t\n\r\f\v";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_SPACE(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "!@#$%^&*()_+{}:\"<>?[];',./\\-=`|~";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_PUNCT(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "()[]{}";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_BRACKET(ch) == accepted);
    }

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        const char accept[] = "!@#$%^&*_+:\"<>?;',./\\-=`|~";
        bool accepted = check_if_character_is_accepted(ch, accept, sizeof(accept) - 1);
        assert(IS_SYMBOL(ch) == accepted);
    }

    printf("Character checks passed!\n");
}

void test_case_conversion(void)
{
    // Test safe conversions (non alphabet characters are passed through)
    {
        char inn[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        char out[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        for (int i = 0; i < (sizeof(inn) - 1); i++)
        {
            assert(TO_UPPER(inn[i]) == out[i]);
        }
    }

    {
        char inn[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        char out[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz0123456789";
        for (int i = 0; i < (sizeof(inn) - 1); i++)
        {
            assert(TO_LOWER(inn[i]) == out[i]);
        }
    }

    {
        char inn[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        char out[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        for (int i = 0; i < (sizeof(inn) - 1); i++)
        {
            assert(TOGGLE_CASE(inn[i]) == out[i]);
        }
    }

    // Test basic conversions
    {
        char inn[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char out[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < (sizeof(inn) - 1); i++)
        {
            assert(FAST_TO_UPPER(inn[i]) == out[i]);
        }
    }

    {
        char inn[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char out[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < (sizeof(inn) - 1); i++)
        {
            assert(FAST_TO_LOWER(inn[i]) == out[i]);
        }
    }

    {
        char inn[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char out[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < (sizeof(inn) - 1); i++)
        {
            assert(FAST_TOGGLE_CASE(inn[i]) == out[i]);
        }
    }

    printf("Case conversion tests passed!\n");
}

void test_conversions(void)
{
    // Test safe conversions

    /* ASCII <-> BINARY */
    assert(ASCII_TO_BINARY('0', -1) == 0);
    assert(ASCII_TO_BINARY('1', -1) == 1);
    assert(ASCII_TO_BINARY('2', -1) == -1);
    assert(ASCII_TO_BINARY('4', -1) == -1);

    assert(BINARY_TO_ASCII(0, -1) == '0');
    assert(BINARY_TO_ASCII(1, -1) == '1');
    assert(BINARY_TO_ASCII(2, -1) == -1);
    assert(BINARY_TO_ASCII(4, -1) == -1);

    assert(FAST_ASCII_TO_BINARY('0') == 0);
    assert(FAST_ASCII_TO_BINARY('1') == 1);

    assert(FAST_BINARY_TO_ASCII(0) == '0');
    assert(FAST_BINARY_TO_ASCII(1) == '1');

    /* ASCII <-> OCTAL */
    assert(ASCII_TO_OCTAL('0', -1) == 0);
    assert(ASCII_TO_OCTAL('1', -1) == 1);
    assert(ASCII_TO_OCTAL('2', -1) == 2);
    assert(ASCII_TO_OCTAL('3', -1) == 3);
    assert(ASCII_TO_OCTAL('4', -1) == 4);
    assert(ASCII_TO_OCTAL('5', -1) == 5);
    assert(ASCII_TO_OCTAL('6', -1) == 6);
    assert(ASCII_TO_OCTAL('7', -1) == 7);
    assert(ASCII_TO_OCTAL(10, -1) == -1);
    assert(ASCII_TO_OCTAL(-10, -1) == -1);

    assert(OCTAL_TO_ASCII(0, -1) == '0');
    assert(OCTAL_TO_ASCII(1, -1) == '1');
    assert(OCTAL_TO_ASCII(2, -1) == '2');
    assert(OCTAL_TO_ASCII(3, -1) == '3');
    assert(OCTAL_TO_ASCII(4, -1) == '4');
    assert(OCTAL_TO_ASCII(5, -1) == '5');
    assert(OCTAL_TO_ASCII(6, -1) == '6');
    assert(OCTAL_TO_ASCII(7, -1) == '7');
    assert(OCTAL_TO_ASCII(10, -1) == -1);
    assert(OCTAL_TO_ASCII(-10, -1) == -1);

    assert(FAST_ASCII_TO_OCTAL('0') == 0);
    assert(FAST_ASCII_TO_OCTAL('1') == 1);
    assert(FAST_ASCII_TO_OCTAL('2') == 2);
    assert(FAST_ASCII_TO_OCTAL('3') == 3);
    assert(FAST_ASCII_TO_OCTAL('4') == 4);
    assert(FAST_ASCII_TO_OCTAL('5') == 5);
    assert(FAST_ASCII_TO_OCTAL('6') == 6);
    assert(FAST_ASCII_TO_OCTAL('7') == 7);

    assert(FAST_OCTAL_TO_ASCII(0) == '0');
    assert(FAST_OCTAL_TO_ASCII(1) == '1');
    assert(FAST_OCTAL_TO_ASCII(2) == '2');
    assert(FAST_OCTAL_TO_ASCII(3) == '3');
    assert(FAST_OCTAL_TO_ASCII(4) == '4');
    assert(FAST_OCTAL_TO_ASCII(5) == '5');
    assert(FAST_OCTAL_TO_ASCII(6) == '6');
    assert(FAST_OCTAL_TO_ASCII(7) == '7');

    /* ASCII <-> DIGIT */
    assert(ASCII_TO_DIGIT('0') == 0);
    assert(ASCII_TO_DIGIT('1') == 1);
    assert(ASCII_TO_DIGIT('2') == 2);
    assert(ASCII_TO_DIGIT('3') == 3);
    assert(ASCII_TO_DIGIT('4') == 4);
    assert(ASCII_TO_DIGIT('5') == 5);
    assert(ASCII_TO_DIGIT('6') == 6);
    assert(ASCII_TO_DIGIT('7') == 7);
    assert(ASCII_TO_DIGIT('8') == 8);
    assert(ASCII_TO_DIGIT('9') == 9);
    assert(ASCII_TO_DIGIT('\0') == -1);
    assert(ASCII_TO_DIGIT('X') == -1);

    assert(DIGIT_TO_ASCII(0, -1) == '0');
    assert(DIGIT_TO_ASCII(1, -1) == '1');
    assert(DIGIT_TO_ASCII(2, -1) == '2');
    assert(DIGIT_TO_ASCII(3, -1) == '3');
    assert(DIGIT_TO_ASCII(4, -1) == '4');
    assert(DIGIT_TO_ASCII(5, -1) == '5');
    assert(DIGIT_TO_ASCII(6, -1) == '6');
    assert(DIGIT_TO_ASCII(7, -1) == '7');
    assert(DIGIT_TO_ASCII(8, -1) == '8');
    assert(DIGIT_TO_ASCII(9, -1) == '9');
    assert(DIGIT_TO_ASCII(10, -1) == -1);
    assert(DIGIT_TO_ASCII(-10, -1) == -1);

    assert(FAST_ASCII_TO_DIGIT('0') == 0);
    assert(FAST_ASCII_TO_DIGIT('1') == 1);
    assert(FAST_ASCII_TO_DIGIT('2') == 2);
    assert(FAST_ASCII_TO_DIGIT('3') == 3);
    assert(FAST_ASCII_TO_DIGIT('4') == 4);
    assert(FAST_ASCII_TO_DIGIT('5') == 5);
    assert(FAST_ASCII_TO_DIGIT('6') == 6);
    assert(FAST_ASCII_TO_DIGIT('7') == 7);
    assert(FAST_ASCII_TO_DIGIT('8') == 8);
    assert(FAST_ASCII_TO_DIGIT('9') == 9);

    assert(FAST_DIGIT_TO_ASCII(0) == '0');
    assert(FAST_DIGIT_TO_ASCII(1) == '1');
    assert(FAST_DIGIT_TO_ASCII(2) == '2');
    assert(FAST_DIGIT_TO_ASCII(3) == '3');
    assert(FAST_DIGIT_TO_ASCII(4) == '4');
    assert(FAST_DIGIT_TO_ASCII(5) == '5');
    assert(FAST_DIGIT_TO_ASCII(6) == '6');
    assert(FAST_DIGIT_TO_ASCII(7) == '7');
    assert(FAST_DIGIT_TO_ASCII(8) == '8');
    assert(FAST_DIGIT_TO_ASCII(9) == '9');

    /* ASCII <-> HEX */
    assert(HEX_TO_INT('0', -1) == 0x00);
    assert(HEX_TO_INT('1', -1) == 0x01);
    assert(HEX_TO_INT('2', -1) == 0x02);
    assert(HEX_TO_INT('3', -1) == 0x03);
    assert(HEX_TO_INT('4', -1) == 0x04);
    assert(HEX_TO_INT('5', -1) == 0x05);
    assert(HEX_TO_INT('6', -1) == 0x06);
    assert(HEX_TO_INT('7', -1) == 0x07);
    assert(HEX_TO_INT('8', -1) == 0x08);
    assert(HEX_TO_INT('9', -1) == 0x09);
    assert(HEX_TO_INT('a', -1) == 0x0A);
    assert(HEX_TO_INT('b', -1) == 0x0B);
    assert(HEX_TO_INT('c', -1) == 0x0C);
    assert(HEX_TO_INT('d', -1) == 0x0D);
    assert(HEX_TO_INT('e', -1) == 0x0E);
    assert(HEX_TO_INT('f', -1) == 0x0F);
    assert(HEX_TO_INT('A', -1) == 0x0A);
    assert(HEX_TO_INT('B', -1) == 0x0B);
    assert(HEX_TO_INT('C', -1) == 0x0C);
    assert(HEX_TO_INT('D', -1) == 0x0D);
    assert(HEX_TO_INT('E', -1) == 0x0E);
    assert(HEX_TO_INT('F', -1) == 0x0F);
    assert(HEX_TO_INT('G', -1) == -1);
    assert(HEX_TO_INT('X', -1) == -1);
    assert(HEX_TO_INT('\0', -1) == -1);

    assert(FAST_UPPERCASE_HEX_TO_INT('0') == 0x00);
    assert(FAST_UPPERCASE_HEX_TO_INT('1') == 0x01);
    assert(FAST_UPPERCASE_HEX_TO_INT('2') == 0x02);
    assert(FAST_UPPERCASE_HEX_TO_INT('3') == 0x03);
    assert(FAST_UPPERCASE_HEX_TO_INT('4') == 0x04);
    assert(FAST_UPPERCASE_HEX_TO_INT('5') == 0x05);
    assert(FAST_UPPERCASE_HEX_TO_INT('6') == 0x06);
    assert(FAST_UPPERCASE_HEX_TO_INT('7') == 0x07);
    assert(FAST_UPPERCASE_HEX_TO_INT('8') == 0x08);
    assert(FAST_UPPERCASE_HEX_TO_INT('9') == 0x09);
    assert(FAST_UPPERCASE_HEX_TO_INT('A') == 0x0A);
    assert(FAST_UPPERCASE_HEX_TO_INT('B') == 0x0B);
    assert(FAST_UPPERCASE_HEX_TO_INT('C') == 0x0C);
    assert(FAST_UPPERCASE_HEX_TO_INT('D') == 0x0D);
    assert(FAST_UPPERCASE_HEX_TO_INT('E') == 0x0E);
    assert(FAST_UPPERCASE_HEX_TO_INT('F') == 0x0F);

    assert(FAST_LOWERCASE_HEX_TO_INT('0') == 0x00);
    assert(FAST_LOWERCASE_HEX_TO_INT('1') == 0x01);
    assert(FAST_LOWERCASE_HEX_TO_INT('2') == 0x02);
    assert(FAST_LOWERCASE_HEX_TO_INT('3') == 0x03);
    assert(FAST_LOWERCASE_HEX_TO_INT('4') == 0x04);
    assert(FAST_LOWERCASE_HEX_TO_INT('5') == 0x05);
    assert(FAST_LOWERCASE_HEX_TO_INT('6') == 0x06);
    assert(FAST_LOWERCASE_HEX_TO_INT('7') == 0x07);
    assert(FAST_LOWERCASE_HEX_TO_INT('8') == 0x08);
    assert(FAST_LOWERCASE_HEX_TO_INT('9') == 0x09);
    assert(FAST_LOWERCASE_HEX_TO_INT('a') == 0x0A);
    assert(FAST_LOWERCASE_HEX_TO_INT('b') == 0x0B);
    assert(FAST_LOWERCASE_HEX_TO_INT('c') == 0x0C);
    assert(FAST_LOWERCASE_HEX_TO_INT('d') == 0x0D);
    assert(FAST_LOWERCASE_HEX_TO_INT('e') == 0x0E);
    assert(FAST_LOWERCASE_HEX_TO_INT('f') == 0x0F);

    assert(NIBBLE_TO_UPPERCASE_HEX(0x00, -1) == '0');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x01, -1) == '1');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x02, -1) == '2');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x03, -1) == '3');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x04, -1) == '4');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x05, -1) == '5');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x06, -1) == '6');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x07, -1) == '7');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x08, -1) == '8');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x09, -1) == '9');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x0A, -1) == 'A');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x0B, -1) == 'B');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x0C, -1) == 'C');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x0D, -1) == 'D');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x0E, -1) == 'E');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x0F, -1) == 'F');
    assert(NIBBLE_TO_UPPERCASE_HEX(0x1F, -1) == -1);

    assert(NIBBLE_TO_LOWERCASE_HEX(0x00, -1) == '0');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x01, -1) == '1');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x02, -1) == '2');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x03, -1) == '3');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x04, -1) == '4');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x05, -1) == '5');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x06, -1) == '6');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x07, -1) == '7');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x08, -1) == '8');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x09, -1) == '9');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x0A, -1) == 'a');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x0B, -1) == 'b');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x0C, -1) == 'c');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x0D, -1) == 'd');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x0E, -1) == 'e');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x0F, -1) == 'f');
    assert(NIBBLE_TO_LOWERCASE_HEX(0x1F, -1) == -1);

    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x00) == '0');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x01) == '1');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x02) == '2');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x03) == '3');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x04) == '4');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x05) == '5');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x06) == '6');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x07) == '7');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x08) == '8');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x09) == '9');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x0A) == 'A');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x0B) == 'B');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x0C) == 'C');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x0D) == 'D');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x0E) == 'E');
    assert(FAST_NIBBLE_TO_UPPERCASE_HEX(0x0F) == 'F');

    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x00) == '0');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x01) == '1');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x02) == '2');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x03) == '3');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x04) == '4');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x05) == '5');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x06) == '6');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x07) == '7');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x08) == '8');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x09) == '9');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x0A) == 'a');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x0B) == 'b');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x0C) == 'c');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x0D) == 'd');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x0E) == 'e');
    assert(FAST_NIBBLE_TO_LOWERCASE_HEX(0x0F) == 'f');

    printf("Conversion tests passed!\n");
}

int main()
{
    test_character_checks();
    test_case_conversion();
    test_conversions();
    printf("All tests passed successfully!\n");
    return 0;
}
