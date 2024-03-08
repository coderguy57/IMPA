#include <fstream>
#include <iostream>
#include <cstdint>

#include <string>

bool do_case(std::istream &input)
{
    int v, t;
    input >> v >> t;
    if (input)
        std::cout << 2 * v * t << "\n";

    return bool(input);
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (do_case(input));
}