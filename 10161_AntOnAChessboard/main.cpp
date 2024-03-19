#include <fstream>
#include <iostream>
#include <cstdint>

#include <cmath>
#include <utility>

void do_case(int N) {
    int sqrt = std::sqrt(N);
    if (sqrt*sqrt != N)
        sqrt++;
    
    int x, y;
    if (N > sqrt*sqrt - sqrt) {
        y = sqrt*sqrt - N + 1;
        x = sqrt;
    } else {
        x = N - (sqrt-1)*(sqrt-1);
        y = sqrt;
    }
    if (sqrt % 2 == 1)
        std::swap(x, y);
    
    std::cout << x << " " << y << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int N;
    while (input >> N && N) {
        do_case(N);
    }
}