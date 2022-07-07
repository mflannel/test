#include <stdio.h>

typedef struct decimal {
    int bits[4];
}s21_decimal;

int get_bit(s21_decimal num, int pos) {
    int result = (num.bits[pos / 32] >> (pos % 32)) & 1;
    return result;
}

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

typedef struct {
    // unsigned char mantissa[29];
    int exponent;
    int sign;
} info;

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
        return 1;
    else
        return 0;
}


void parseExp(s21_decimal *bits, info *dst) {
    int j = 0;
    for (int i = 16; i <= 23; i++) {
        set_bit_nums(&dst->exponent, get_bit_nums( bits->bits[3], i), j);
        j++;
    }
}

int isSet(int x, int pos) {
    return ((x >> pos) & 1U);
}

int main() {



    printf("Hello, World!\n");
    return 0;
}
