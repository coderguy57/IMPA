#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <queue>

struct Edge {
    int to;
    int weight;

    bool operator>(const Edge &other) const {
        return weight > other.weight;
    }
};

void do_case(std::istream &input, int test_case)
{
    int n, m, S, T;
    input >> n >> m >> S >> T;

    std::vector<std::vector<Edge>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        input >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    pq.push({S, 0});
    std::vector<int> dist(n, INT32_MAX);

    while (!pq.empty())
    {
        Edge current = pq.top();
        pq.pop();

        if (dist[current.to] <= current.weight)
            continue;

        dist[current.to] = current.weight;

        if (current.to == T)
            break;

        for (Edge &neighbour : graph[current.to])
        {
            if (dist[neighbour.to] <= current.weight + neighbour.weight)
                continue;

            pq.push({neighbour.to, current.weight + neighbour.weight});
        }
    }

    if (dist[T] == INT32_MAX)
    {
        std::cout << "Case #" << test_case << ": unreachable" << std::endl;
    }
    else
    {
        std::cout << "Case #" << test_case << ": " << dist[T] << std::endl;
    }
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
        do_case(input, i + 1);
    }
}