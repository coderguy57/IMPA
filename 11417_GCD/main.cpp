#include <fstream>
#include <iostream>
#include <cstdint>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    
    return gcd(b, a % b);
}

void do_case(int N) {
    int G=0;
    for(int i=1; i<N ;i++) {
        for(int j=i+1; j<=N; j++) {
            G += gcd(i,j);
        }
    }

    std::cout << G << std::endl;
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