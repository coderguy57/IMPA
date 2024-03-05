#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <algorithm>

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

template<typename T>
struct Edge
{
    int u, v;
    T cost;
    bool operator<(const Edge &other) const
    {
        return cost < other.cost;
    }
};

std::vector<int> MST(std::vector<Edge<int>> &edges, int N)
{
    std::sort(edges.begin(), edges.end());
    UnionFind uf(N);
    std::vector<int> mst(N - 1);
    int num_edges = 0;
    for (int i = 0; i < edges.size(); i++)
    {
        auto& edge = edges[i];
        if (uf.same(edge.u, edge.v))
            continue;

        uf.unite(edge.u, edge.v);
        mst.push_back(i);
        num_edges++;
        if (num_edges == N - 1)
            break;
    }
    return mst;
}

bool do_case(std::istream &input) {
    int m, n;
    input >> m >> n;
    if (m == 0 && n == 0) {
        return false;
    }

    std::vector<Edge<int>> edges(n);
    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        int u, v, cost;
        input >> u >> v >> cost;
        total_cost += cost;
        edges.push_back({u, v, cost});
    }

    std::vector<int> mst = MST(edges, m);
    int cost_saved = total_cost;
    for (auto i : mst) {
        cost_saved -= edges[i].cost;
    }
    std::cout << cost_saved << std::endl;
    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (do_case(input));
}