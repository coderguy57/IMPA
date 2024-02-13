#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

const int N = 1000;
int DP[(N + 1) * (N + 1)];
inline int get_index(int i, int j) { return (i + 1) * N + j + 1; }

void do_case(std::string& s1, std::string& s2) {
    for (int i = 0; i < s1.size(); i++) {
        for (int j = 0; j < s2.size(); j++) {
            auto val = std::max(DP[get_index(i - 1, j)], DP[get_index(i, j - 1)]);
            if (s1[i] == s2[j]) {
                val = std::max(val, DP[get_index(i - 1, j - 1)] + 1);
            }
            DP[get_index(i, j)] = val;
        }
    }
    
    std::cout << DP[get_index(s1.size() - 1, s2.size() - 1)] << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    std::fill(DP, DP + ((N + 1) * (N + 1)), 0);

    std::string s1, s2;
    getline(input, s1);
    getline(input, s2);
    while (input) {
        do_case(s1, s2);
        getline(input, s1);
        getline(input, s2);
    }
}