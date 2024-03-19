#include <fstream>
#include <iostream>
#include <cstdint>

#include <string>
#include <cstdlib>

int get_min_base(const std::string &str)
{
    int min_base = 2;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            min_base = std::max(min_base, c - '0' + 1);
        else
            min_base = std::max(min_base, c - 'A' + 11);
    }
    return min_base;
}

long long string_to_long(const std::string &str, int base)
{
    long long result = 0;
    for (char c : str)
    {
        result = result * base + (c >= '0' && c <= '9' ? c - '0' : c - 'A' + 10);
    }
    return result;
}

bool do_case(std::istream &input)
{
    std::string str1, str2;
    input >> str1 >> str2;
    if (!input)
        return false;
    
    int min_base1 = get_min_base(str1);
    int min_base2 = get_min_base(str2);

    for (int base1 = min_base1; base1 <= 36; base1++)
    {
        for (int base2 = min_base2; base2 <= 36; base2++)
        {
            if (string_to_long(str1, base1) == string_to_long(str2, base2))
            {
                std::cout << str1 << " (base " << base1 << ") = " << str2 << " (base " << base2 << ")" << std::endl;
                return true;
            }
        }
    }
    std::cout << str1 << " is not equal to " << str2 << " in any base 2..36" << std::endl;
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