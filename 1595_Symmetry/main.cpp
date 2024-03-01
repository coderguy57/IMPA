#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <algorithm>

struct Point
{
    int x, y;
};

struct SymmetryCompare
{
    int mid;
    bool operator()(const Point &a, const Point &b) const
    {
        bool left = 2 * a.x < mid;
        return a.x < b.x || (a.x == b.x && (a.y < b.y) ^ left);
    }
};

void do_case(std::istream &input)
{
    int N;
    input >> N;
    if (N == 0)
    {
        std::cout << "YES\n";
        return;
    }

    std::vector<Point> p(N);
    int max = INT32_MIN, min = INT32_MAX;
    for (int i = 0; i < N; i++)
    {
        input >> p[i].x >> p[i].y;
        max = std::max(max, p[i].x);
        min = std::min(min, p[i].x);
    }
    int mid = max + min;
    std::sort(p.begin(), p.end(), SymmetryCompare{mid});


    int i = 0, j = N - 1;
    while (i <= j)
    {
        if (p[i].x + p[j].x != mid)
        {
            std::cout << "NO\n";
            return;
        }
        if (p[i].x != p[j].x && p[i].y != p[j].y)
        {
            std::cout << "NO\n";
            return;
        }
        i++;
        j--;
    }
    std::cout << "YES\n";
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int T;
    input >> T;
    for (int i = 0; i < T; i++)
    {
        do_case(input);
    }
}