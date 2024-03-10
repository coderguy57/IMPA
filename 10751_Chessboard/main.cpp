#include <fstream>
#include <iostream>
#include <cstdint>

#include <cmath>
#include <iomanip>

void do_case(std::istream &input)
{
    int n;
    input >> n;

    std::cout << std::fixed << std::setprecision(3);
    if (n == 1) {
        std::cout << 0. << std::endl;
    } else {
        double res = n * n;
        res += (n - 2) * (n - 2) * (std::sqrt(2) - 1);
        std::cout << res << std::endl;
    }
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int T;
    input >> T;
    for (int i = 0; i < T; i++)
    {
        do_case(input);
        if (i < T - 1)
            std::cout << std::endl;
    }
}