#include <fstream>
#include <iostream>
#include <stdint.h>

#include <array>
#include <vector>
#include <bitset>
#include <string>
#include <cmath>

int size;

int &at(std::vector<int> &A, int i, int j)
{
    return A[i * size + j];
}

std::vector<int> multiply(std::vector<int> &A, std::vector<int> &B)
{
    std::vector<int> C(A.size(), INT_LEAST32_MIN);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                at(C, i, j) = std::max(at(C, i, j), at(A, i, k) + at(B, k, j));

    return C;
}

bool do_case(std::istream &input)
{
    int C, S, E, T;
    input >> C >> S >> E >> T;
    if (C + S + E + T == 0)
        return false;
    size = C;

    int log = std::max(int(std::log2(T)), 1);
    std::vector<std::vector<int>> power2(log + 1);
    power2[0] = std::vector<int>(C * C);
    for (int i = 0; i < C*C; i++)
    {
        input >> power2[0][i];
        if (power2[0][i] == 0)
            power2[0][i] = INT_LEAST32_MIN;
    }
    std::vector<int> ends(E);
    for (int i = 0; i < E; i++) {
        int end;
        input >> ends[i];
    }
    if (T == 0) {
        printf("%d\n", 0);
        return true;
    }

    for (int i = 1; i <= log; i++)
    {
        power2[i] = multiply(power2[i-1], power2[i-1]);
    }
    std::vector<int> profit(C*C);
    bool set = false;
    for (int i = 0; i <= log; i++) {
        if (T & 1) {
            profit = set ? multiply(profit, power2[i]) : power2[i];
            set = true;
        }
        T = T >> 1;
    }

    int best = INT_LEAST32_MIN;
    for (int i = 0; i < ends.size(); i++) {
        best = std::max(best, at(profit, S - 1, ends[i] - 1));
    }
    best = std::max(best, 0);


    printf("%d\n", best);
    
    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (do_case(input))
    {
    }
}