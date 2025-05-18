/* Includes you should need */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ROUNDUP 0
#define ROUNDDOWN 1
#define ROUNDTOEVEN 2

/**
 * Part 1.1
 * @brief You'll be converting a Binary string into it's unsigned decimal value.
 * @param input_string the binary string you'll be converting to decimal.
 * @return the converting decimal value (an unsigned long)
 */
unsigned long binary_to_unsigned_decimal(const char *input_string)
{
    unsigned long sum = 0;
    size_t len = strlen(input_string);
    for (size_t i = 0; i < len; i++) {
        if (input_string[i] == '1') {
            sum += 1UL << (len - 1 - i);
        }
    }
    return sum;
}
/**
 * Part 1.2
 * @brief You'll be converting a binary string into it's decimal value using the signed magnitude representation
 * @param input_string, the binary string you'll be converting to decimal
 * @return the signed decimal value (a signed long type using signed magnitude)
 */
long binary_to_signed_magnitude_decimal(const char *input_string)
{
    size_t len = strlen(input_string);
    if (len == 0) return 0;

    int sign = (input_string[0] == '1') ? -1 : 1;
    unsigned long magnitude = 0;
    for (size_t i = 1; i < len; i++) {
        if (input_string[i] == '1') {
            magnitude += 1UL << (len - 1 - i);
        }
    }
    return sign * (long)magnitude;
}
/**
 * Part 1.2
 * @brief You'll be converting a binary string into it's decimal value using ones complement.
 * @param input_string, the binary string you'll be converting to decimal
 * @return the signed decimal value (a signed long type using ones complement)
 */
long binary_to_ones_complement_decimal(const char *input_string)
{
    size_t len = strlen(input_string);
    if (len == 0) return 0;

    if (input_string[0] == '0') {
        return (long)binary_to_unsigned_decimal(input_string);
    } else {
        unsigned long inverted = 0;
        for (size_t i = 0; i < len; i++) {
            char bit = input_string[i];
            char inverted_bit = (bit == '1') ? '0' : '1';
            if (inverted_bit == '1') {
                inverted += 1UL << (len - 1 - i);
            }
        }
        return - (long)inverted;
    }
}
/**
 * Part 1.4
 * @brief Convert a Binary string into it's decimal value using twos complement.
 * @param input_string: The string you're going to convert to decimal
 * @return the unsigned long using twos complement
 */
long binary_to_twos_complement_decimal(const char *input_string)
{
size_t len = strlen(input_string);
    if (len == 0) return 0;

    if (input_string[0] == '0') {
        return (long)binary_to_unsigned_decimal(input_string);
    } else {
        unsigned long unsigned_val = binary_to_unsigned_decimal(input_string);

        // 手动计算符号位对应的值，避免 1UL << 64
        unsigned long sign_bit_val = 1UL << (len - 1);

        return (long)(unsigned_val - 2 * sign_bit_val);
    }
}
/**
 * part 2.1
 * @brief In this part, you'll be converting an unsigned decimal value into it's unsigned binary representation
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *unsigned_decimal_to_binary(unsigned long input, unsigned int numbits)
{
char *result = malloc(numbits + 1);
    if (!result) return NULL;
    for (unsigned int i = 0; i < numbits; i++) {
        result[i] = (input & (1UL << (numbits - 1 - i))) ? '1' : '0';
    }
    result[numbits] = '\0';
    return result;
}
/**
 * part 2.1
 * @brief In this part, you'll be converting an unsigned decimal value into it's binary representation using signed magnitude
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *signed_decimal_to_signed_magnitude(long input, unsigned int numbits)
{
char *result = malloc(numbits + 1);
    if (!result) return NULL;
    int sign = (input < 0) ? 1 : 0;
    result[0] = sign ? '1' : '0';
    unsigned long magnitude = (input < 0) ? -input : input;

    for (unsigned int i = 1; i < numbits; i++) {
        result[i] = (magnitude & (1UL << (numbits - 1 - i))) ? '1' : '0';
    }
    result[numbits] = '\0';
    return result;
}
/**
 * part 2.1
 * @brief In this part, you'll be converting an unsigned decimal value into it's ones complement binary representation
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *signed_decimal_to_ones_complement(long input, unsigned int numbits)
{
char *result = malloc(numbits + 1);
    if (!result) return NULL;
    if (input >= 0) {
        for (unsigned int i = 0; i < numbits; i++) {
            result[i] = ((unsigned long)input & (1UL << (numbits - 1 - i))) ? '1' : '0';
        }
    } else {
        unsigned long pos = -input;
        for (unsigned int i = 0; i < numbits; i++) {
            char bit = (pos & (1UL << (numbits - 1 - i))) ? '1' : '0';
            result[i] = (bit == '1') ? '0' : '1';
        }
    }
    result[numbits] = '\0';
    return result;
}
/**
 * part 2.1
 * @brief In this part, you'll be converting an unsigned decimal value into it's two complement binary representation
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *signed_decimal_to_twos_complement(long input, unsigned int numbits)
{
char *result = malloc(numbits + 1);
    if (!result) return NULL;
    if (input >= 0) {
        for (unsigned int i = 0; i < numbits; i++) {
            result[i] = (((unsigned long)input) & (1UL << (numbits - 1 - i))) ? '1' : '0';
        }
    } else {
        unsigned long value;
        if (numbits == 64)
            value = (unsigned long)input;
        else
            value = (1UL << numbits) + (unsigned long)input;
        for (unsigned int i = 0; i < numbits; i++) {
            result[i] = (value & (1UL << (numbits - 1 - i))) ? '1' : '0';
        }
    }
    result[numbits] = '\0';
    return result;
}
/**
 * Part 3.1
 * @brief In this part, you'll be converting an ieee754 string with a specified number of exponent and mantissa bits into it's decimal value (always 1 sign bit).
 * @param input the ieee 754 string to convert into it's decimal value.
 * @param exp The number of exponent bits in the input string.
 * @param mantissa The number of mantissa bits in the input string.
 */
double ieee754_to_decimal(char *input, int exp, int mantissa)
{
int total_bits = 1 + exp + mantissa;
    if ((int)strlen(input) != total_bits) return 0.0;

    int sign = input[0] - '0';

    int exponent = 0;
    for (int i = 0; i < exp; i++) {
        exponent = (exponent << 1) | (input[1 + i] - '0');
    }

    double mantissa_val = 0.0;
    for (int i = 0; i < mantissa; i++) {
        if (input[1 + exp + i] == '1') {
            mantissa_val += pow(2.0, -(i + 1));
        }
    }

    int bias = (1 << (exp - 1)) - 1;

    if (exponent == (1 << exp) - 1 && mantissa_val > 0) return NAN;

    double value;
    if (exponent == 0) {
        value = mantissa_val * pow(2.0, 1 - bias);
    } else {
        value = (1.0 + mantissa_val) * pow(2.0, exponent - bias);
    }

    return sign ? -value : value;
}
/**
 * part 3.2
 * @brief In this part, you'll be converting a decimal value, and converting it into it's ieee 754 representation given the number of exp, mantissa bits, and what rounding mode to use.
 * @param input The number you'll be converting into it's ieee 754 representation
 * @param exp_bits The number of exponent bits your representation should have.
 * @param mantissa_bits The number of mantissa bits your representation should have.
 * @param rounding_mode The rounding mode you should use: 0 to round up, 1 to round down, 2 for round to even.
 */
char *decimal_to_ieee754_binary(double input, int exp_bits, int mantissa_bits, int rounding_mode)
{
printf("%d %d %d\n", ROUNDUP, ROUNDDOWN, ROUNDTOEVEN);
int total_bits = 1 + exp_bits + mantissa_bits;
    char *res = malloc(total_bits + 1);
    if (!res) return NULL;
    memset(res, '0', total_bits);
    res[total_bits] = '\0';

    int sign = input < 0.0 ? 1 : 0;
    res[0] = sign + '0';
    if (input == 0.0) return res;

    double abs_val = fabs(input);
    int e;
    double frac = frexp(abs_val, &e);
    frac *= 2;
    e--;

    int bias = (1 << (exp_bits - 1)) - 1;
    int exp_field = e + bias;
    if (exp_field <= 0) {
        frac = abs_val / pow(2, 1 - bias);
        exp_field = 0;
    }
    if (exp_field >= (1 << exp_bits) - 1) exp_field = (1 << exp_bits) - 1;

    for (int i = exp_bits - 1; i >= 0; i--) {
        res[1 + exp_bits - 1 - i] = ((exp_field >> i) & 1) + '0';
    }

    double frac_part = (exp_field == 0) ? frac : frac - 1.0;
    int grs_bits = mantissa_bits + 3;
    unsigned long long mantissa_raw = 0;
    for (int i = 0; i < grs_bits; i++) {
        frac_part *= 2.0;
        mantissa_raw <<= 1;
        if (frac_part >= 1.0) {
            mantissa_raw |= 1;
            frac_part -= 1.0;
        }
    }

    int R = (mantissa_raw >> 2) & 1;
    int S = (mantissa_raw & 3) ? 1 : 0;
    mantissa_raw >>= 3;

    int round_up = 0;
    if (rounding_mode == ROUNDUP && (R || S)) {
        round_up = 1;
    } else if (rounding_mode == ROUNDTOEVEN && R && (S || (mantissa_raw & 1))) {
        round_up = 1;
    }

    if (round_up) {
        mantissa_raw++;
        if (mantissa_raw == (1ULL << mantissa_bits)) {
            mantissa_raw = 0;
            exp_field++;
            if (exp_field < (1 << exp_bits)) {
                for (int i = exp_bits - 1; i >= 0; i--) {
                    res[1 + exp_bits - 1 - i] = ((exp_field >> i) & 1) + '0';
                }
            }
        }
    }

    for (int i = mantissa_bits - 1; i >= 0; i--) {
        res[1 + exp_bits + mantissa_bits - 1 - i] = ((mantissa_raw >> i) & 1) + '0';
    }

    return res;
}
