#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

const int N = std::pow(std::sqrt(1299709)+1, 2);
std::vector<int> sieve(N, 1);

// Generate all primes up to N
void init() {
    int sqrtN = std::sqrt(N);
    for (int i = 2; i <= sqrtN; i++) {
        if (sieve[i]) {
            for (int j = i * i; j < N; j += i)
                sieve[j] = 0;
        }
    }
}

void do_case(int num) {
    int left, right;
    left = right = num;

    while (!sieve[left]) {
        left--;
    }
    while (!sieve[right]) {
        right++;
    }

    std::cout << right - left << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    init();

    int num;
    while(input >> num && num) {
        do_case(num);
    }
}