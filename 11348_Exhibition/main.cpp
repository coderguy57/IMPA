#include <fstream>
#include <iostream>
#include <stdint.h>

#include <vector>
#include <set>
#include <iomanip>
#include <array>

std::array<int, 10001> stamp_counts;

void do_case(std::istream &input, int k)
{
    int N;
    input >> N;
    std::vector<std::set<int>> friends;
    stamp_counts.fill(0);

    for (int n = 0; n < N; n++) {
        friends.push_back({});
        int M;
        input >> M;
        for (int m = 0; m < M; m++) {
            int stamp;
            input >> stamp;
            if (!friends[n].count(stamp)) {
                friends[n].insert(stamp);
                stamp_counts[stamp]++;
            }
        }
    }
    int total_unique = 0;
    for (int n = 0; n < N; n++) {
        for (auto& stamp : friends[n]) {
            if (stamp_counts[stamp] == 1)
                total_unique++;
        }
    }

    std::cout << "Case " << k << ":";
    for (int n = 0; n < N; n++) {
        double unique_count = 0;
        for (auto& stamp : friends[n]) {
            if (stamp_counts[stamp] == 1)
                unique_count++;
        }
        std::cout << " " << 100. * unique_count / total_unique << "%";
    }
    std::cout << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    int K;
    input >> K;
    for (int k = 1; k <= K; k++)
    {
        do_case(input, k);
    }
}