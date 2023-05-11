/*
 * 1. Напишите функцию, которая принимает на вход знаковое целое число и
 * печатает его двоичное представление, не используя библиотечных классов или функций. 
 */


// вариант, где будет печать в прямой форме
template <typename Int>
void printIntegerInBinary(Int num) {
    const size_t bitsInByte = 8;
    const size_t count = bitsInByte * sizeof(Int);

    int result[count] = {};
    Int degree = 1;
    const size_t last_idx = count - 1u;

     if (num < 0) {
        num *= (-1);
        result[last_idx] = 1;
    }

    for (size_t i = 0u; i < last_idx; ++i) {
        const Int bit = (num & degree) >> i;
        result[i] = bit;
        degree = degree << 1;
    }

    for (int i = last_idx; i >= 0; --i) {
        printf("%d", result[i]);
    }
}
