#include <fstream>
#include <iostream>
#include <cstdint>

#include <string>

void do_case(std::istream &input)
{
    std::string s;
    input >> s;
    int n = s.size();
    s += s;

    int best = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s[best+j] < s[i+j]) {
                i += j;
                break;
            } else if (s[best+j] > s[i+j]) {
                best = i;
                break;
            }
        }
    }

    std::cout << s.substr(best, n) << "\n";
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
    }
}