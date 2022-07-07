#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "s21_decimal.h"

int get_bit(s21_decimal num, int pos);

void set_bit(s21_decimal *val, int bit, int pos) {
    if (bit != 0) {
        val->bits[pos/32] = val->bits[pos/32] | (bit << pos);
    }
}

int get_bit_nums(int num, int pos) {             //  howiter
    int result = (num >> (pos % 32)) & 1;
    return result;
}

void set_bit_nums(int *val, int bit, int pos) {  //  howieter
    if (bit != 0) {
        *val = *val | (bit << pos);
    }
}


// void get_info(s21_decimal num, info *dec_info){
//     int i = 16;
//     int j = 0;
//     int k = 0;
//     dec_info->sign = get_bit(num, 31);
//     while (i < 24){
//         k = get_bit(num, i);
//             set_bit(dec_info->exponent, k, j);
//         i++;
//         j++;
//     }
// }

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res = 0;
    int *tmp = (int*)calloc(32*4, sizeof(int));
    int j = 0;
    for (int i = 0; i < 96; i++) {
        for (int k = 0; k < 32; k++) {
            set_bit_nums(&tmp[j], get_bit_nums(value_1.bits[i/32], k) & get_bit_nums(value_2.bits[i/32], i), k);
        }
        if (i != 0 && i != 32 && i != 64) {
            tmp[j] = tmp[j] << j;
        }
        j++;

        if (j == 31) {
            int buffer = 0;
            for (int a = 0; a < 32; a++) {
                int flag = 0;
                int b = 0;
                int buffer = 0;
                int n = get_bit_nums(tmp[a], b);
                int m = get_bit_nums(result->bits[i/32], b);
                int res = n ^ m;

                if (n == 1 && m == 1)
                    flag = 1;
                set_bit(result, res, b);
                b++;

                while (b < 32) {
                    n = get_bit_nums(tmp[a], b);
                    m = get_bit_nums(result->bits[i/32], b);
                    res = n ^ m;
                    if (res == 1 && flag == 1)
                        res = res ^ flag;
                    else if (flag == 1) {
                        res = res ^ flag;
                        flag = 0;
                    }
                    if (n == 1 && m == 1)
                        flag = 1;
                    set_bit(result, res, b);
                    i++;
                }
                tmp[a] = 0;
            }
        }
    }
    free(tmp);
    return res;
}

int s21_add(s21_decimal a, s21_decimal b, s21_decimal *result){
    int flag = 0;
    int i = 0;
    int n = get_bit(a, i);
    int m = get_bit(b, i);
    int res = n ^ m;

    if (n == 1 && m == 1)
        flag = 1;
    set_bit(result, res, i);
    i++;

    while (i < 95)
    {
        n = get_bit(a, i);
        m = get_bit(b, i);
        res = n ^ m;
        if (res == 1 && flag == 1)
            res = res ^ flag;
        else if (flag == 1){
            res = res ^ flag;
            flag = 0;
        }
        if (n == 1 && m == 1)
            flag = 1;
        set_bit(result, res, i);
        i++;
    }

    if (flag == 1)
        return TOO_LARGE_OR_INF;
    else
        return OK;
}


void set_exp(s21_decimal* a, info* info_a,  s21_decimal* b, info* info_b) {
    int i = 7;
    int res = 0;
    int n= 0;
    int m = 0;
    s21_decimal ten = {10,0,0,0};
    s21_decimal result = {0,0,0,0};

    while (i > 0){
        n = get_bit_nums(info_a->exponent, i);
        m = get_bit_nums(info_b->exponent, i);
        if (n == 0 && m == 1){
            res = 1;  // exp b > exp a => a > b
            break;
        }
        if (n == 1 && m == 0){
            res = 0;
            break;
        }
        else
            i--;
    }
    if (res == 1) {
        s21_mul(ten, *b, &result);
        info_b->exponent = info_a->exponent;
    } else {
        s21_mul(ten, *a, &result);
        info_a->exponent = info_b->exponent;
    }
}



// int s21_is_less(s21_decimal a, s21_decimal b){
//     int i = 8;
//     int res = 0;
//     int n = 0;
//     int m = 0;
//     info dec_info_a = {0};
//     info dec_info_b = {0};

//     get_info(a, &get_info);
//     get_info(b, &get_info);

//     if (dec_info_a.sign == 1 && dec_info_b.sign == 0)
//         res = 1;
//     else if (dec_info_a.sign == 0 && dec_info_b.sign == 1)
//         res = 0;
//     else {
//         while (i > -1){
// n = get_bit(dec_info_a.exponent, i); "ЭКСПОНЕНТА"
// m = get_bit(dec_info_b.exponent, i);
// if (n == 1 && m == 0){
//     res = 1;
//     break;
// }
//         if (n == 0 && m == 1){
//             res = 0;
//             break;
//         }
//         i--;
//         }
//         i = 95;
//         while (i > -1){
//             n = get_bit(a, i);
//             m = get_bit(b, i);
//             if (n == 0 && m == 1){
//                 res = 1;
//                 break;
//             }
//             if (n == 1 && m == 0){
//                 res = 0;
//                 break;
//             }
//             i--;
//         }
//     }
//     return res;
// }

int get_bit(s21_decimal num, int pos) {
    int result = (num.bits[pos / 32] >> (pos % 32)) & 1;
    return result;
}

char* IntToBinary(unsigned int n) {
    char* binary = (char*)malloc(sizeof(char) * (32 + 1));
    int k = 0;
    for (unsigned i = (1 << (32 - 1)); i > 0; i = i / 2) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';
    return binary;
}

int main(void) {
    s21_decimal a = {3, 0, 0, 0};
    s21_decimal b = {3, 0, 0, 0};
    s21_decimal c = {0, 0, 0, 0};

    char *binary3 = IntToBinary(a.bits[3]);
    char *binary2 = IntToBinary(a.bits[2]);
    char *binary1 = IntToBinary(a.bits[1]);
    char *binary0 = IntToBinary(a.bits[0]);
    printf("%s %s %s\n %s\n\n", binary2, binary1, binary0, binary3);

    char *binary32 = IntToBinary(b.bits[3]);
    char *binary22 = IntToBinary(b.bits[2]);
    char *binary12 = IntToBinary(b.bits[1]);
    char *binary02 = IntToBinary(b.bits[0]);
    printf("%s %s %s\n %s\n\n", binary22, binary12, binary02, binary32);

    printf("\n%d\n", s21_mul(a, b, &c));
    //set_bit(&a, 1, 4);

    char *binary33 = IntToBinary(c.bits[3]);
    char *binary23 = IntToBinary(c.bits[2]);
    char *binary13 = IntToBinary(c.bits[1]);
    char *binary03 = IntToBinary(c.bits[0]);
    printf("%s %s %s\n %s\n\n", binary23, binary13, binary03, binary33);
    return 0;
}