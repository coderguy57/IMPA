#include <fstream>
#include <iostream>
#include <cstdint>

/* by Jim Ulery */
uint32_t isqrt(uint64_t val) {
    uint64_t temp, g=0, b = 0x80000000, bshft = 31;
    do {
        if (val >= (temp = (((g << 1) + b)<<bshft--))) {
           g += b;
           val -= temp;
        }
    } while (b >>= 1);
    return g;
}

void do_case(std::istream &input) {
    uint64_t N;
    input >> N;

    auto result = (isqrt(8 * N + 1) - 1) / 2;
    std::cout << result << "\n";
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
    for (int t = 0; t < T; t++)
    {
        do_case(input);
    }
}