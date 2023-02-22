#include <fstream>
#include <iostream>
#include <iomanip>
#include <array>
#include <cstring>

std::array<std::array<int, 8>, 101> pref;
std::array<std::array<int, 8>, 101> results;

uint8_t get_result(int m, int current) {
    if (results[m][current] != -1)
        return results[m][current];
    if (m == 0) {
        uint8_t choice1 = pref[0][current^0b001];
        uint8_t choice2 = pref[0][current^0b010];
        uint8_t choice3 = pref[0][current^0b100];
        if (choice1 < choice2) {
            if (choice1 < choice3)
                return results[m][current] = current^0b001;
            else
                return results[m][current] = current^0b100;
        } else {
            if (choice2 < choice3)
                return results[m][current] = current^0b010;
            else
                return results[m][current] = current^0b100;
        }
    }
uint8_t choice1 = pref[m][get_result(m-1, current^0b001)];
    uint8_t choice2 = pref[m][get_result(m-1, current^0b010)];
    uint8_t choice3 = pref[m][get_result(m-1, current^0b100)];
    if (choice1 < choice2) {
        if (choice1 < choice3)
            return results[m][current] = get_result(m-1, current^0b001);
        else
            return results[m][current] = get_result(m-1, current^0b100);
    } else {
        if (choice2 < choice3)
            return results[m][current] = get_result(m-1, current^0b010);
        else
            return results[m][current] = get_result(m-1, current^0b100);
    }
}

int main() {
    // std::ifstream input("input.txt");
    std::istream& input = std::cin;

    std::string res[] = {"NNN", "NNY", "NYN", "NYY", "YNN", "YNY", "YYN", "YYY"};

    int N, M;
    input >> N;
    for (int n = 0; n < N; n++) {
        input >> M;
        for (int m = M; m --> 0;) {
            for (int i = 0; i < 8; i++) {
                input >> pref[m][i];
            }
        }
        
        memset(&results,-1,sizeof(results));
        std::cout << res[get_result(M-1, 0b000)] << std::endl;
    }
    
}