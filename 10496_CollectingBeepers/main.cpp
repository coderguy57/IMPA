#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cstring>

int memo[11][1 << 10];
int dist[11][11];

int dp(uint32_t mask, int u) { // mask = free coordinates
    if (mask == 0) return dist[u][0]; // close the tour
    int &ans = memo[u][mask];
    if (ans != -1) return ans;
    ans = 2000000000;
    int m = mask;
    while (m) { // up to O(n)
        int two_pow_v = m & (-m); // isolate the rightmost bit
        int v = __builtin_ctz(two_pow_v)+1; // offset v by +1
        ans = std::min(ans, dist[u][v] + dp(mask^two_pow_v, v)); // keep the min
        m -= two_pow_v;
    }
    return ans;
}

void do_case(std::istream& input) {
    int size_x, size_y;
    input >> size_x >> size_y;
    int x0, y0;
    input >> x0 >> y0;
    int n;
    input >> n;
    std::vector<std::pair<int, int>> beepers(n+1);
    beepers[0] = std::make_pair(x0, y0);
    for (int i = 1; i < n+1; i++)
        input >> beepers[i].first >> beepers[i].second;

    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < n+1; j++) {
            dist[j][i] = dist[i][j] = std::abs(beepers[i].first - beepers[j].first) + std::abs(beepers[i].second - beepers[j].second);
        }
    }
    std::memset(memo, -1, sizeof(memo));

    std::cout << "The shortest path has length " << dp((1 << n) - 1, 0) << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int N = 0;
    input >> N;
    for (int i = 0; i < N; i++) {
        do_case(input);
    }
}