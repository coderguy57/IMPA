#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

int m;

struct matrix {
    uint64_t a, b, c, d;
    matrix operator*(const matrix& other) const {
        return {
            (a * other.a + b * other.c) % m,
            (a * other.b + b * other.d) % m,
            (c * other.a + d * other.c) % m,
            (c * other.b + d * other.d) % m
        };
    }
};

matrix matrix_power(matrix&& base, int exponent) {
    if (exponent == 1)
        return base;
    else if (exponent % 2 == 0)
        return matrix_power(base * base, exponent / 2);
    else
        return base * matrix_power(base * base, (exponent - 1) / 2);
}

void do_case(int n) {
    matrix base = {1, 1, 1, 0};
    if (n < 2) {
        std::cout << n % m << std::endl;
        return;
    }
    matrix result = matrix_power(std::move(base), n - 1);
    std::cout << result.a << std::endl;    
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int n;
    while(input >> n >> m) {
        m = std::pow(2, m);
        do_case(n);
    }
}