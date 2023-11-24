#include <fstream>
#include <iostream>
#include <stdint.h>

#include <array>
#include <numeric>
#include <bitset>
#include <string>

bool do_case(std::istream &input, int collection) {
    std::array<int, 6> count;
    for (auto& c : count)
        input >> c;

    int sum = std::accumulate(count.begin(), count.end(), 0);
    if (sum == 0)
        return false;
    
    std::bitset<128> states(0);
    states[64] = 1;
    for (int n = 1; n <= 6; n++) {
        auto c = count[n-1];
        if (c > 0) {
            if (n <= 3) {
                count[n*2-1] += (c - 1) / 2;
                c = ((c - 1) % 2) + 1;
            } else {
                c = c % 2 + 2 * std::min(c / 2, 7);
            }
        }
        for (int i = 0; i < c; i++) {
            auto l_state = states << n;
            auto r_state = states >> n;
            states = l_state | r_state;
        }
    }


    // std::cout << states << std::endl;
    // auto s = states.to_string();
    // fprintf(file,"%s:\n", s.c_str());
    printf("Collection #%d:\n", collection);
    if (states[64])
        printf("Can be divided.\n\n");
    else
        printf("Can't be divided.\n\n");

    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int i = 1;
    while (do_case(input, i++))
    {
    }
}