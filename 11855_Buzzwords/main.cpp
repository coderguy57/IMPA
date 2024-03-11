#include <fstream>
#include <iostream>
#include <cstdint>

#include <string>
#include <vector>
#include <numeric>
#include <cstring>
#include <algorithm>

void do_case(std::istream &input)
{
    std::string s;
    getline(input, s);
    if (!input)
        return;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    if (s.empty()) {
        return;
    }

    int n = s.size();
    std::vector<int> SA(n);
    std::iota(SA.begin(), SA.end(), 0);
    sort(SA.begin(), SA.end(), [&s](int a, int b) {
        return strcmp(s.c_str()+a, s.c_str()+b) < 0;
    });

    std::vector<int> LCP(n);
    LCP[0] = 0;
    for (int i = 1; i < n; ++i) {
        int L = 0;
        while ((SA[i]+L < n) && (SA[i-1]+L < n) &&
            (s[SA[i]+L] == s[SA[i-1]+L])) ++L;
        LCP[i] = L;
    }

    for (int i = 1; i < n; i++) {
        int longest = 1;
        int current = 1;
        for (int j = 0; j < n; j++) {
            if (LCP[j] < i) {
                current = 1;
            } else {
                current++;
                longest = std::max(longest, current);                
            }
        }
        if (longest == 1) {
            break;
        } else {
            std::cout << longest << "\n";
        }
    }
    std::cout << "\n";
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (input) {
        do_case(input);
    }
}