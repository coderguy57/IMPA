#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>

bool do_case(std::istream& input) {
    int n;
    if (!(input >> n)) {
        return false;
    }
    std::vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        input >> numbers[i];
    }

    std::vector<bool> diffs(n, false);
    for (int i = 1; i < n; i++) {
        int diff = std::abs(numbers[i] - numbers[i - 1]);
        if (diff < diffs.size()) {
            diffs[diff] = true;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!diffs[i]) {
            std::cout << "Not jolly" << std::endl;
            return true;
        }
    }
    std::cout << "Jolly" << std::endl;
    return true;

}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (do_case(input)) {}
}