#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>

using ii = std::pair<int, int>;
using iii = std::tuple<int, int, int>;

struct UnionFind
{
    std::vector<int> parent;
    std::vector<int> rank;
    int components;

    UnionFind(int n) : parent(n), rank(n, 0), components(n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    void unite(int x, int y)
    {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x == root_y)
        {
            return;
        }
        if (rank[root_x] > rank[root_y])
        {
            parent[root_y] = root_x;
        }
        else
        {
            parent[root_x] = root_y;
            if (rank[root_x] == rank[root_y])
            {
                rank[root_y]++;
            }
        }
        components--;
    }
};

iii find_smallest_edge(const std::vector<ii> &cities, UnionFind& city_connection)
{
    int N = cities.size();
    int min_distance = INT32_MAX;
    ii min_edge;
    for (int i = 0; i < N; i++)
    {
        int xi, yi;
        std::tie(xi, yi) = cities[i];
        for (int j = i + 1; j < N; j++)
        {
            if (city_connection.same(i, j))
            {
                continue;
            }
            int xj, yj;
            std::tie(xj, yj) = cities[j];
            auto x_diff = (xi - xj) * (xi - xj);
            if (x_diff > min_distance)
            {
                break;
            }
            auto y_diff = (yi - yj) * (yi - yj);
            if (x_diff + y_diff < min_distance)
            {
                min_distance = x_diff + y_diff;
                min_edge = {i, j};
            }
        }
    }
    return {min_edge.first, min_edge.second, min_distance};
}

void do_case(std::istream &input, int case_number) {
    int N, R;
    input >> N >> R;

    std::vector<ii> cities(N);
    for (int i = 0; i < N; i++) {
        input >> cities[i].first >> cities[i].second;
    }
    std::sort(cities.begin(), cities.end());
    
    double roads = 0, railroads = 0;

    UnionFind city_connection(N);
    UnionFind state_connection(N);

    while (city_connection.components > 1) {
        int i, j, distance_squared;
        std::tie(i, j, distance_squared) = find_smallest_edge(cities, city_connection);
        auto distance = std::sqrt(distance_squared);
        if (distance <= R) {
            roads += distance;
            state_connection.unite(i, j);
        } else {
            railroads += distance;
        }
        city_connection.unite(i, j);
    }


    std::cout 
        << "Case #" << case_number << ": " 
        << state_connection.components << " " 
        << std::round(roads) << " " 
        << std::round(railroads) << "\n";
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int case_number = 1;
    int T;
    input >> T;
    for (int t = 0; t < T; t++)
    {
        do_case(input, case_number++);
    }
}