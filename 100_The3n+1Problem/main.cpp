#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>

std::vector<int> cycle_lengths = std::vector<int>(100000, 0);

int cycle_length(int n)
{
    if (n < cycle_lengths.size() && cycle_lengths[n] != 0)
        return cycle_lengths[n];
    if (n == 1)
        return 1;

    int length = 1;
    if (n % 2 == 0)
        length += cycle_length(n / 2);
    else
        length += cycle_length(3 * n + 1);

    if (n < cycle_lengths.size())
        cycle_lengths[n] = length;

    return length;
}

bool do_case(std::istream &input)
{
    int i, j;
    input >> i >> j;
    if (!input)
        return false;

    int max_length = 0;
    for (int n = std::min(i, j); n <= std::max(i, j); ++n)
    {
        int length = cycle_length(n);
        if (length > max_length)
            max_length = length;
    }
    std::cout << i << " " << j << " " << max_length << std::endl;
    return true;
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