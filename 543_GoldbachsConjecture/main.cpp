#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

const int N = 1000000;
std::vector<int> primes;
std::vector<int> prime_index = std::vector<int>(N, 0);

// Generate all primes up to N
void init() {
    std::vector<int> sieve(N, 1);
    int sqrtN = std::sqrt(N);
    for (int i = 2; i <= sqrtN; i++) {
        if (sieve[i]) {
            primes.push_back(i);
            for (int j = i * i; j < N; j += i)
                sieve[j] = 0;
        }
        prime_index[i] = primes.size();
    }
    // Add the rest of the primes
    for (int i = sqrtN + 1; i < N; i++) {
        if (sieve[i]) {
            primes.push_back(i);
        }
        prime_index[i] = primes.size();
    }
}

void do_case(int num) {
    int start = 0;
    int end = prime_index[num] - 1;
    while (start <= end) {
        int sum = primes[start] + primes[end];
        if (sum == num) {
            std::cout << num << " = " << primes[start] << " + " << primes[end] << std::endl;
            return;
        } else if (sum < num) {
            start++;
        } else {
            end--;
        }
    }
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