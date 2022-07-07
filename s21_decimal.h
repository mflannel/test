#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CONVERT_ERROR 1
#define CONVERT_OK 0

typedef struct {
    int bits[4];
} s21_decimal;

typedef struct {
    // unsigned char mantissa[29];
    int exponent;
    int sign;
} info;

enum {low, mid, top, scale};

char* IntToBinary(unsigned int n);


int get_bit_nums(int num, int pos);             //  howieter
void set_bit_nums(int *val, int bit, int pos);  //  howieter

int get_bit(s21_decimal num, int pos);
void set_bit(s21_decimal *val, int bit, int pos);

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
#define CONVERT_ERROR 1
#define COMPAR_TRUE 1
#define COMPAR_FALSE 0
#define TOO_LARGE_OR_INF 1
#define TOO_SMALL_OR_NEG_INF 2
#define DIV_BY_ZERO 3
#define OK 0



#endif  // SRC_S21_DECIMAL_H_