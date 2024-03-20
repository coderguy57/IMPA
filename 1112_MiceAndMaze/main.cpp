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

void do_case(std::istream &input)
{
    int N, E, T, M;
    input >> N >> E >> T >> M;
    E--;

    std::vector<std::vector<Edge>> graph(N);
    for (int i = 0; i < M; i++)
    {
        int a, b, t;
        input >> a >> b >> t;
        graph[b - 1].push_back({a - 1, t});
    }

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    pq.push({E, 0});
    std::vector<int> dist(N, INT32_MAX);

    int count = 0;
    while (!pq.empty())
    {
        Edge current = pq.top();
        pq.pop();

        if (current.weight > T)
            break;
        if (dist[current.to] <= current.weight)
            continue;

        dist[current.to] = current.weight;
        count++;

        for (Edge &neighbour : graph[current.to])
        {
            if (dist[neighbour.to] <= current.weight + neighbour.weight)
                continue;

            pq.push({neighbour.to, current.weight + neighbour.weight});
        }
    }

    std::cout << count << std::endl;
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
        if (i < T - 1)
            std::cout << std::endl;
    }
}