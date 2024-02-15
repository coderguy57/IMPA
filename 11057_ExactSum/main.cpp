#include <fstream>
#include <iostream>
#include <cstdint>

#include <iterator>
#include <vector>
#include <algorithm>

void do_case(std::istream &input) {
    int N;
    input >> N;
    if (!input)
        return;
    
    std::vector<int> numbers(N);
    for (int i = 0; i < N; i++)
        input >> numbers[i];

    int M;
    input >> M;
    
    std::sort(numbers.begin(), numbers.end());
    int start = 0;
    int end = numbers.size() - 1;
    std::pair<int, int> best_index;
    int max_price = 0;
    while (start < end) {
        int price = numbers[start] + numbers[end];
        if (price <= M) {
            if (price >= max_price) {
                best_index = std::make_pair(numbers[start], numbers[end]);
                max_price = price;
            }
            start++;
        }
        else
            end--;
    }

    std::cout << "Peter should buy books whose prices are "
        << best_index.first << " and " << best_index.second << ".\n" << std::endl;

    std::string s;
    getline(input, s);
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while(input) {
        do_case(input);
    }
}