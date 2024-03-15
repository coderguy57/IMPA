#include <fstream>
#include <iostream>
#include <cstdint>

void do_case(std::istream& input) {
    int n;
    input >> n;

    n = n * 567;
    n = n / 9;
    n = n + 7492;
    n = n * 235;
    n = n / 47;
    n = n - 498;
    n = n / 10;
    n = std::abs(n);
    n = n % 10;

    std::cout << n << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int N = 0;
    input >> N;
    for (int i = 0; i < N; i++) {
        do_case(input);
    }
}