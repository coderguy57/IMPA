#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

const int N = 1000;
int DP[(N + 1) * N];
inline int get_index(int i, int j) { return i * N + j; }

struct CompareStrings {
    std::string& s;
    
    bool operator()(const int& dp_index1, const int& dp_index2) {
        auto end_index1 = (dp_index1 % N) + 1;
        auto end_index2 = (dp_index2 % N) + 1;
        auto start_index1 = end_index1 - DP[dp_index1];
        auto start_index2 = end_index2 - DP[dp_index2];
        return std::lexicographical_compare(s.begin() + start_index1, s.begin() + end_index1,
                                            s.begin() + start_index2, s.begin() + end_index2);
    }
};

int countOccurrences(const std::string& str, const std::string& sub) {
    if (sub.empty()) return 0;

    int count = 0;
    std::size_t pos = 0;

    // Use std::string::npos for the end-of-string marker
    while ((pos = str.find(sub, pos)) != std::string::npos) {
        ++count;
        pos++;
    }

    return count;
}

void do_case(std::istream& input) {
    std::string s;
    input >> s;

    std::vector<int> indices;
    int max = 0;
    for (int i = 1; i < s.size() + 1; i++) {
        for (int j = i; j < s.size(); j++) {
            if (s[i - 1] == s[j]) {
                auto val = DP[get_index(i - 1, j - 1)] + 1;
                DP[get_index(i, j)] = val;
                if (val >= max) {
                    if (val > max)
                        indices.clear();
                    max = std::max(val, max);
                    indices.push_back(get_index(i, j));
                }
            } else {
                DP[get_index(i, j)] = 0;
            }
        }
    }
    
    if (max == 0) {
        std::cout << "No repetitions found!" << std::endl;
    } else {
		auto dp_index = *std::min_element(indices.begin(), indices.end(), CompareStrings{s});
        auto end_index = (dp_index % N) + 1;
        auto start_index = end_index - DP[dp_index];
        auto subsequence = s.substr(start_index, end_index - start_index); 
        auto count = countOccurrences(s, subsequence);
        std::cout << subsequence << " " << count << std::endl;
    }

}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    std::fill(DP, DP + ((N + 1) * N), 0);

    int T;
    input >> T;
    for (int t = 0; t < T; t++) {
        do_case(input);
    }
}