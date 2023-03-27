#include <fstream>
#include <iostream>
#include <stdint.h>

#include <vector>
#include <set>
#include <iomanip>
#include <array>

std::array<int, 1000> cycles;
std::array<int, 1000*10> milk;

void do_case(std::istream &input)
{
    int N;
    input >> N;
    int C = N;
    int D = 0;

    for (int n = 0; n < N; n++) {
        input >> cycles[n];
        for (int j = 0; j < cycles[n]; j++) {
            input >> milk[n*10 + j];
        }
    }

    int max = 2*3*2*5*7*2*3;
    int count = 0;
    int day = 0;
    while (count < max) {
        int32_t min = INT32_MAX;
        int dead_cow = -1;
        for (int n = 0; n < N; n++) {
            if (cycles[n] == 0)
                continue; // DEAD

            int cow_milk = milk[n*10 + (day % cycles[n])];
            if (cow_milk == min) {
                dead_cow = -1;
            }
            if (cow_milk < min) {
                dead_cow = n;
                min = cow_milk;
            }
        }
        count++;
        day++;
        if (dead_cow != -1) {
            cycles[dead_cow] = 0;
            count = 0;
            C--;
            D = day;
        }
    }

    std::cout << C << " " << D << std::endl;
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
    for (int t = 1; t <= T; t++)
    {
        do_case(input);
    }
}