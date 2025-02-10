#include "char-utils.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static_assert(CHARUTIL_DIGIT_COUNT == CHARUTIL_DIGIT_COUNT_GROKKABLE);
static_assert(CHARUTIL_ALPHABET_COUNT == CHARUTIL_ALPHABET_COUNT_GROKKABLE);
static_assert(CHARUTIL_ALPHANUMERIC_COUNT == CHARUTIL_ALPHANUMERIC_COUNT_GROKKABLE);

void test_character_checks(void)
{
    // Test basic checks
    assert(IS_DIGIT('5') && !IS_DIGIT('a'));
    assert(IS_LOWER('a') && !IS_LOWER('A'));
    assert(IS_UPPER('Z') && !IS_UPPER('z'));
    assert(IS_ALPHA('a') && IS_ALPHA('Z') && !IS_ALPHA('5'));
    assert(IS_ALNUM('a') && IS_ALNUM('5') && !IS_ALNUM('#'));
    assert(IS_HEX_DIGIT('F') && IS_HEX_DIGIT('f') && !IS_HEX_DIGIT('G'));
    assert(IS_SPACE(' ') && IS_SPACE('\n') && !IS_SPACE('x'));

    for (int ch = -0x1FF; ch < 0x1FF; ch++)
    {
        assert(IS_DIGIT(ch) == IS_DIGIT_GROKKABLE(ch));
        assert(IS_LOWER(ch) == IS_LOWER_GROKKABLE(ch));
        assert(IS_UPPER(ch) == IS_UPPER_GROKKABLE(ch));
        assert(IS_ALPHA(ch) == IS_ALPHA_GROKKABLE(ch));
        assert(IS_ALNUM(ch) == IS_ALNUM_GROKKABLE(ch));
        assert(IS_HEX_DIGIT(ch) == IS_HEX_DIGIT_GROKKABLE(ch));
        assert(IS_SPACE(ch) == IS_SPACE_GROKKABLE(ch));
        assert(IS_PRINTABLE(ch) == IS_PRINTABLE_GROKKABLE(ch));
        assert(IS_ASCII(ch) == IS_ASCII_GROKKABLE(ch));
        assert(IS_EXTENDED_ASCII(ch) == IS_EXTENDED_ASCII_GROKKABLE(ch));
    }

    printf("Character checks passed!\n");
}

void test_case_conversion(void)
{
    // Test basic conversions
    {
        char in[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char out[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < (sizeof(in) - 1); i++)
        {
            assert(TO_UPPER(in[i]) == out[i]);
        }
    }

    {
        char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char out[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < (sizeof(in) - 1); i++)
        {
            assert(TO_LOWER(in[i]) == out[i]);
        }
    }

    {
        char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char out[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < (sizeof(in) - 1); i++)
        {
            assert(TOGGLE_CASE(in[i]) == out[i]);
        }
    }

    // Test safe conversions (non alphabet characters are passed through)
    {
        char in[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        char out[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        for (int i = 0; i < (sizeof(in) - 1); i++)
        {
            assert(SAFE_TO_UPPER(in[i]) == out[i]);
        }
    }

    {
        char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        char out[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz0123456789";
        for (int i = 0; i < (sizeof(in) - 1); i++)
        {
            assert(SAFE_TO_LOWER(in[i]) == out[i]);
        }
    }

    {
        char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        char out[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        for (int i = 0; i < (sizeof(in) - 1); i++)
        {
            assert(SAFE_TOGGLE_CASE(in[i]) == out[i]);
        }
    }

    printf("Case conversion tests passed!\n");
}

void test_conversions(void)
{
    // Test basic conversions
    assert(DIGIT_TO_ASCII(0) == '0');
    assert(DIGIT_TO_ASCII(1) == '1');
    assert(DIGIT_TO_ASCII(2) == '2');
    assert(DIGIT_TO_ASCII(3) == '3');
    assert(DIGIT_TO_ASCII(4) == '4');
    assert(DIGIT_TO_ASCII(5) == '5');
    assert(DIGIT_TO_ASCII(6) == '6');
    assert(DIGIT_TO_ASCII(7) == '7');
    assert(DIGIT_TO_ASCII(8) == '8');
    assert(DIGIT_TO_ASCII(9) == '9');

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

    assert(HEX_TO_INT('0') == 0x00);
    assert(HEX_TO_INT('1') == 0x01);
    assert(HEX_TO_INT('2') == 0x02);
    assert(HEX_TO_INT('3') == 0x03);
    assert(HEX_TO_INT('4') == 0x04);
    assert(HEX_TO_INT('5') == 0x05);
    assert(HEX_TO_INT('6') == 0x06);
    assert(HEX_TO_INT('7') == 0x07);
    assert(HEX_TO_INT('8') == 0x08);
    assert(HEX_TO_INT('9') == 0x09);
    assert(HEX_TO_INT('a') == 0x0A);
    assert(HEX_TO_INT('b') == 0x0B);
    assert(HEX_TO_INT('c') == 0x0C);
    assert(HEX_TO_INT('d') == 0x0D);
    assert(HEX_TO_INT('e') == 0x0E);
    assert(HEX_TO_INT('f') == 0x0F);
    assert(HEX_TO_INT('A') == 0x0A);
    assert(HEX_TO_INT('B') == 0x0B);
    assert(HEX_TO_INT('C') == 0x0C);
    assert(HEX_TO_INT('D') == 0x0D);
    assert(HEX_TO_INT('E') == 0x0E);
    assert(HEX_TO_INT('F') == 0x0F);

    assert(NIBBLE_TO_HEX(0x00) == '0');
    assert(NIBBLE_TO_HEX(0x01) == '1');
    assert(NIBBLE_TO_HEX(0x02) == '2');
    assert(NIBBLE_TO_HEX(0x03) == '3');
    assert(NIBBLE_TO_HEX(0x04) == '4');
    assert(NIBBLE_TO_HEX(0x05) == '5');
    assert(NIBBLE_TO_HEX(0x06) == '6');
    assert(NIBBLE_TO_HEX(0x07) == '7');
    assert(NIBBLE_TO_HEX(0x08) == '8');
    assert(NIBBLE_TO_HEX(0x09) == '9');
    assert(NIBBLE_TO_HEX(0x0A) == 'A');
    assert(NIBBLE_TO_HEX(0x0B) == 'B');
    assert(NIBBLE_TO_HEX(0x0C) == 'C');
    assert(NIBBLE_TO_HEX(0x0D) == 'D');
    assert(NIBBLE_TO_HEX(0x0E) == 'E');
    assert(NIBBLE_TO_HEX(0x0F) == 'F');

    assert(NIBBLE_TO_HEX_UPPER(0x00) == '0');
    assert(NIBBLE_TO_HEX_UPPER(0x01) == '1');
    assert(NIBBLE_TO_HEX_UPPER(0x02) == '2');
    assert(NIBBLE_TO_HEX_UPPER(0x03) == '3');
    assert(NIBBLE_TO_HEX_UPPER(0x04) == '4');
    assert(NIBBLE_TO_HEX_UPPER(0x05) == '5');
    assert(NIBBLE_TO_HEX_UPPER(0x06) == '6');
    assert(NIBBLE_TO_HEX_UPPER(0x07) == '7');
    assert(NIBBLE_TO_HEX_UPPER(0x08) == '8');
    assert(NIBBLE_TO_HEX_UPPER(0x09) == '9');
    assert(NIBBLE_TO_HEX_UPPER(0x0A) == 'A');
    assert(NIBBLE_TO_HEX_UPPER(0x0B) == 'B');
    assert(NIBBLE_TO_HEX_UPPER(0x0C) == 'C');
    assert(NIBBLE_TO_HEX_UPPER(0x0D) == 'D');
    assert(NIBBLE_TO_HEX_UPPER(0x0E) == 'E');
    assert(NIBBLE_TO_HEX_UPPER(0x0F) == 'F');

    assert(NIBBLE_TO_HEX_LOWER(0x00) == '0');
    assert(NIBBLE_TO_HEX_LOWER(0x01) == '1');
    assert(NIBBLE_TO_HEX_LOWER(0x02) == '2');
    assert(NIBBLE_TO_HEX_LOWER(0x03) == '3');
    assert(NIBBLE_TO_HEX_LOWER(0x04) == '4');
    assert(NIBBLE_TO_HEX_LOWER(0x05) == '5');
    assert(NIBBLE_TO_HEX_LOWER(0x06) == '6');
    assert(NIBBLE_TO_HEX_LOWER(0x07) == '7');
    assert(NIBBLE_TO_HEX_LOWER(0x08) == '8');
    assert(NIBBLE_TO_HEX_LOWER(0x09) == '9');
    assert(NIBBLE_TO_HEX_LOWER(0x0A) == 'a');
    assert(NIBBLE_TO_HEX_LOWER(0x0B) == 'b');
    assert(NIBBLE_TO_HEX_LOWER(0x0C) == 'c');
    assert(NIBBLE_TO_HEX_LOWER(0x0D) == 'd');
    assert(NIBBLE_TO_HEX_LOWER(0x0E) == 'e');
    assert(NIBBLE_TO_HEX_LOWER(0x0F) == 'f');

    // Test safe conversions
    assert(SAFE_DIGIT_TO_ASCII(0) == '0');
    assert(SAFE_DIGIT_TO_ASCII(1) == '1');
    assert(SAFE_DIGIT_TO_ASCII(2) == '2');
    assert(SAFE_DIGIT_TO_ASCII(3) == '3');
    assert(SAFE_DIGIT_TO_ASCII(4) == '4');
    assert(SAFE_DIGIT_TO_ASCII(5) == '5');
    assert(SAFE_DIGIT_TO_ASCII(6) == '6');
    assert(SAFE_DIGIT_TO_ASCII(7) == '7');
    assert(SAFE_DIGIT_TO_ASCII(8) == '8');
    assert(SAFE_DIGIT_TO_ASCII(9) == '9');
    assert(SAFE_DIGIT_TO_ASCII(10) == '\0');
    assert(SAFE_DIGIT_TO_ASCII(-10) == '\0');

    assert(SAFE_ASCII_TO_DIGIT('0') == 0);
    assert(SAFE_ASCII_TO_DIGIT('1') == 1);
    assert(SAFE_ASCII_TO_DIGIT('2') == 2);
    assert(SAFE_ASCII_TO_DIGIT('3') == 3);
    assert(SAFE_ASCII_TO_DIGIT('4') == 4);
    assert(SAFE_ASCII_TO_DIGIT('5') == 5);
    assert(SAFE_ASCII_TO_DIGIT('6') == 6);
    assert(SAFE_ASCII_TO_DIGIT('7') == 7);
    assert(SAFE_ASCII_TO_DIGIT('8') == 8);
    assert(SAFE_ASCII_TO_DIGIT('9') == 9);
    assert(SAFE_ASCII_TO_DIGIT('\0') == -1);
    assert(SAFE_ASCII_TO_DIGIT('X') == -1);

    assert(SAFE_HEX_TO_INT('0') == 0x00);
    assert(SAFE_HEX_TO_INT('1') == 0x01);
    assert(SAFE_HEX_TO_INT('2') == 0x02);
    assert(SAFE_HEX_TO_INT('3') == 0x03);
    assert(SAFE_HEX_TO_INT('4') == 0x04);
    assert(SAFE_HEX_TO_INT('5') == 0x05);
    assert(SAFE_HEX_TO_INT('6') == 0x06);
    assert(SAFE_HEX_TO_INT('7') == 0x07);
    assert(SAFE_HEX_TO_INT('8') == 0x08);
    assert(SAFE_HEX_TO_INT('9') == 0x09);
    assert(SAFE_HEX_TO_INT('a') == 0x0A);
    assert(SAFE_HEX_TO_INT('b') == 0x0B);
    assert(SAFE_HEX_TO_INT('c') == 0x0C);
    assert(SAFE_HEX_TO_INT('d') == 0x0D);
    assert(SAFE_HEX_TO_INT('e') == 0x0E);
    assert(SAFE_HEX_TO_INT('f') == 0x0F);
    assert(SAFE_HEX_TO_INT('A') == 0x0A);
    assert(SAFE_HEX_TO_INT('B') == 0x0B);
    assert(SAFE_HEX_TO_INT('C') == 0x0C);
    assert(SAFE_HEX_TO_INT('D') == 0x0D);
    assert(SAFE_HEX_TO_INT('E') == 0x0E);
    assert(SAFE_HEX_TO_INT('F') == 0x0F);
    assert(SAFE_HEX_TO_INT('G') == -1);
    assert(SAFE_HEX_TO_INT('X') == -1);

    assert(SAFE_NIBBLE_TO_HEX(0x00) == '0');
    assert(SAFE_NIBBLE_TO_HEX(0x01) == '1');
    assert(SAFE_NIBBLE_TO_HEX(0x02) == '2');
    assert(SAFE_NIBBLE_TO_HEX(0x03) == '3');
    assert(SAFE_NIBBLE_TO_HEX(0x04) == '4');
    assert(SAFE_NIBBLE_TO_HEX(0x05) == '5');
    assert(SAFE_NIBBLE_TO_HEX(0x06) == '6');
    assert(SAFE_NIBBLE_TO_HEX(0x07) == '7');
    assert(SAFE_NIBBLE_TO_HEX(0x08) == '8');
    assert(SAFE_NIBBLE_TO_HEX(0x09) == '9');
    assert(SAFE_NIBBLE_TO_HEX(0x0A) == 'A');
    assert(SAFE_NIBBLE_TO_HEX(0x0B) == 'B');
    assert(SAFE_NIBBLE_TO_HEX(0x0C) == 'C');
    assert(SAFE_NIBBLE_TO_HEX(0x0D) == 'D');
    assert(SAFE_NIBBLE_TO_HEX(0x0E) == 'E');
    assert(SAFE_NIBBLE_TO_HEX(0x0F) == 'F');
    assert(SAFE_NIBBLE_TO_HEX(0x1F) == '\0');

    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x00) == '0');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x01) == '1');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x02) == '2');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x03) == '3');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x04) == '4');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x05) == '5');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x06) == '6');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x07) == '7');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x08) == '8');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x09) == '9');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x0A) == 'A');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x0B) == 'B');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x0C) == 'C');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x0D) == 'D');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x0E) == 'E');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x0F) == 'F');
    assert(SAFE_NIBBLE_TO_HEX_UPPER(0x1F) == '\0');

    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x00) == '0');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x01) == '1');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x02) == '2');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x03) == '3');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x04) == '4');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x05) == '5');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x06) == '6');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x07) == '7');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x08) == '8');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x09) == '9');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x0A) == 'a');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x0B) == 'b');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x0C) == 'c');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x0D) == 'd');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x0E) == 'e');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x0F) == 'f');
    assert(SAFE_NIBBLE_TO_HEX_LOWER(0x1F) == '\0');

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
