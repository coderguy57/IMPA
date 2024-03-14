#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

const int N = 1000000;
std::vector<int> sieve(N, 1);

// Generate all primes up to N
void init() {
    sieve[0] = sieve[1] = 0;
    int sqrtN = std::sqrt(N);
    for (int i = 2; i <= sqrtN; i++) {
        if (sieve[i]) {
            for (int j = i * i; j < N; j += i)
                sieve[j] = 0;
        }
    }
}

bool check(int n, int gap) {
    if (!sieve[n+gap])
        return false;
    int curr = n + (gap > 0 ? 1 : -1);
    while (curr != (n + gap)) {
        if (sieve[curr])
            return false;
        curr += gap > 0 ? 1 : -1;
    }
    return true;
}

void print_consecutive(int curr, int gap, int consecutive) {
    if (check(curr, gap))
        return;
    curr -= gap * (consecutive - 1);
    if (check(curr, -gap))
        return;
    while (consecutive--) {
        std::cout << curr;
        if (consecutive > 0)
            std::cout << " ";
        else
            std::cout << std::endl;
        curr += gap;
    }
}

bool do_case(std::istream& input) {
    int left, right;
    input >> left >> right;
    if (left == 0 && right == 0)
        return false;
    
    if (left > right)
        std::swap(left, right);

    int gap = 0;
    int last = 0;
    int consecutive = 0;
    left--;
    while (++left <= right) {
        if (!sieve[left])
            continue;
        
        if (last) {
            int current_gap = left - last;
            if (gap == current_gap) {
                consecutive++;
            } else {
                if (consecutive > 0)
                    print_consecutive(last, gap, consecutive + 2);
                gap = current_gap;
                consecutive = 0;
            }
        }
        last = left;
    }
    if (consecutive > 0)
        print_consecutive(last, gap, consecutive + 2);
    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    init();

    while(do_case(input)) {};
}