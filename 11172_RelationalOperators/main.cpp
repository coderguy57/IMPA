#include <fstream>
#include <iostream>
#include <cstdint>

void do_case(std::istream& input) {
    int a, b;
    input >> a >> b;
    
    if (a < b) {
        std::cout << "<" << std::endl;
    } else if (a > b) {
        std::cout << ">" << std::endl;
    } else {
        std::cout << "=" << std::endl;
    }
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