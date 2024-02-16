#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

const int N = 1000000;
std::vector<int> primes;
std::vector<int> numbers;

void init() {
    std::vector<int> sieve(N, 1);
    int sqrtN = std::sqrt(N);
    for (int i = 2; i <= sqrtN; i++) {
        if (sieve[i] == 1) {
            primes.push_back(i);
            numbers.push_back(i);
            for (int j = i * i; j < N; j += i)
                sieve[j] = 0;
            for (int j = i * i; j < N; j *= i)
                sieve[j] = i;
        } else if (sieve[i] != 0) {
            primes.push_back(sieve[i]);
            numbers.push_back(i);
        }
    }
    for (int i = sqrtN + 1; i < N; i++) {
        if (sieve[i] == 1) {
            primes.push_back(i);
            numbers.push_back(i);
        } else if (sieve[i] != 0) {
            primes.push_back(sieve[i]);
            numbers.push_back(i);
        }
    }
}

void do_case(int num) {
    std::vector<int> temp = primes;
    std::vector<int> temp2 = numbers;
    uint64_t res = 1;
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] > num)
            break;
        if (primes[i] == 5)
            res /= 2;
        else
            res *= primes[i];
        res %= N;
    }
    std::cout << res % 10 << std::endl;
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