#include <fstream>
#include <iostream>
#include <cstdint>

void do_case(uint64_t n)
{
    uint64_t test = 1;
    while (test < n) {
        test <<= 1;
    }
    uint64_t best = test;
    while (test % 2 == 0) {
        if (test >= n) {
            best = std::min(best, test);
            test >>= 1;
        } else {
            test *= 3;
        }
    }
    if (test >= n)
        best = std::min(best, test);
    std::cout << best << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    uint64_t num;
    while (input >> num && num)
    {
        do_case(num);
    }
}