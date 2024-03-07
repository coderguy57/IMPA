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
    std::vector<int> mst;
    mst.reserve(N - 1);
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

int i = 0;
bool do_case(std::istream &input) {
    int m, n;
    input >> n >> m;
    if (m == 0 && n == 0) {
        return false;
    }

    std::vector<Edge<int>> edges;
    edges.reserve(m);
    int total_cost = 0;
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        input >> u >> v >> cost;
        total_cost += cost;
        edges.push_back({u, v, cost});
    }

    std::vector<int> mst = MST(edges, n);
    std::vector<int> heavy_cycle_edges;
    heavy_cycle_edges.reserve(edges.size() - mst.size());
    int mst_index = 0;
    for (int i = 0; i < edges.size(); i++) {
        if (mst_index < mst.size() && mst[mst_index] == i) {
            mst_index++;
            continue;
        }
        heavy_cycle_edges.push_back(edges[i].cost);
    }
    std::sort(heavy_cycle_edges.begin(), heavy_cycle_edges.end());
    for (auto& heavy_cycle_edge : heavy_cycle_edges) {
        std::cout << heavy_cycle_edge;
        if (&heavy_cycle_edge != &heavy_cycle_edges.back()) {
            std::cout << " ";
        }
    }
    if (heavy_cycle_edges.empty())
        std::cout << "forest";
    std::cout << "\n";
    i++;
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