#include <fstream>
#include <iostream>
#include <vector>

int main() {
    // std::ifstream input("input.txt");
    std::istream& input = std::cin;

    int a_primes[] = {2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 199, 311, 337, 373, 733, 919, 991};

    int num;
    while (input >> num, num) {

        int start = 22; // 991
        if (num < 100)
            start = 13; // 97
        if (num < 10)
            start = 4;  // 7
            
        int out = 0;
        for (int i = start; i --> 0;) {
            if (a_primes[i] <= num)
                break;
            out = a_primes[i];
        }

        std::cout << out << std::endl;
    }
}