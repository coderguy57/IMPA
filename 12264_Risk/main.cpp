#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <queue>
#include <algorithm>

struct Graph {
    std::vector<std::vector<int>> connections;
    std::vector<int> borders;
    std::vector<int> armies;
    int nodes;

    std::vector<std::vector<int>> flow;
    std::vector<int> supply_flow;
    std::vector<int> demand;

    Graph(std::vector<std::vector<int>> c, std::vector<int> b, std::vector<int> a)
        : connections{c}, borders{b}, armies{a}, nodes{int(armies.size())}
    {
        flow = std::vector<std::vector<int>>(nodes);
        for (int i = 0; i < nodes; i++)
            flow[i] = std::vector<int>(nodes, 0);
        supply_flow = std::vector<int>(nodes, 0);
        demand = std::vector<int>(nodes, 1);
    }
};

Graph get_graph(std::istream& input) {
    int N;
    input >> N;

    int nodes = 0;
    std::vector<int> armies(N);
    for (int n = 0; n < N; n++) {
        input >> armies[n];
        if (armies[n])
            nodes++;

    }
    
    std::vector<std::vector<int>> connections;
    std::vector<int> borders;
    for (int i = 0; i < N; i++) {
        std::string line;
        input >> line;

        if (!armies[i])
            continue;

        int from_index = connections.size();
        connections.emplace_back();
        
        int to_index = 0;
        bool added = 0;
        for (int j = 0; j < N; j++) {
            if (!armies[j]) {
                if ((line[j] == 'Y') && (borders.empty() || borders.back() != from_index))
                    borders.push_back(from_index);
                continue;
            }

            if (line[j] == 'Y')
                connections.back().push_back(to_index);
            else if (from_index == to_index)
                connections.back().push_back(to_index);
            to_index++;
        }
    }

    armies.erase(std::remove(armies.begin(), armies.end(), 0), armies.end());
    return Graph(std::move(connections), std::move(borders), std::move(armies));
}

int find_path(Graph& graph, int start_node, std::vector<int>& parents) {
    std::queue<int> nodes;
    parents = std::vector<int>(graph.nodes * 2, -1);
    std::vector<bool> visited(graph.nodes * 2, false);

    nodes.push(start_node);
    visited[start_node] = true;
    
    while (!nodes.empty()) {
        auto from = nodes.front();
        auto forward = from < graph.nodes;
        nodes.pop();

        if (!forward && graph.demand[from - graph.nodes])
            return from;
        
        auto from_index = forward ? from : from - graph.nodes;
        for (auto& connection : graph.connections[from_index]) {
            int to = forward ? connection + graph.nodes : connection; 
            if (visited[to])
                continue;
            if (!forward && graph.flow[to][from - graph.nodes] == 0)
                continue;
            parents[to] = from;
            visited[to] = true;

            nodes.push(to);
        }
    }
    return -1;
}

void do_flow(Graph& graph, int start_node, int end_node, std::vector<int>& parents) {
    int max_flow = graph.armies[start_node] - graph.supply_flow[start_node];
    max_flow = std::min(graph.demand[end_node - graph.nodes], max_flow);
    int prev_node = end_node;
    int new_node = parents[end_node];
    while (new_node != start_node) {
        if (new_node > prev_node)
            max_flow = std::min(graph.flow[prev_node][new_node - graph.nodes], max_flow);
        prev_node = new_node;
        new_node = parents[new_node];
    }

    prev_node = end_node;
    new_node = parents[end_node];
    graph.supply_flow[start_node] += max_flow;
    graph.flow[new_node][prev_node - graph.nodes] += max_flow;
    while (new_node != start_node) {
        prev_node = new_node;
        new_node = parents[new_node];
        if (new_node > prev_node)
            graph.flow[prev_node][new_node - graph.nodes] -= max_flow;
        else
            graph.flow[new_node][prev_node - graph.nodes] += max_flow;
    }
    graph.demand[end_node - graph.nodes] -= max_flow;
}

bool max_flow(Graph& graph) {
    auto& armies = graph.armies;
    auto& flow = graph.flow;
    auto& supply_flow = graph.supply_flow;

    std::vector<int> parents;
    bool updated;
    do {
        updated = false;
        for (int i = 0; i < graph.nodes; i++) {
            if (supply_flow[i] == armies[i])
                continue;

            auto end_node = find_path(graph, i, parents);
            if (end_node != -1) {
                do_flow(graph, i, end_node, parents);
                updated = true;
            }
        }
    } while (updated);

    bool done = true;
    for (int i = 0; i < graph.nodes; i++)
        done = graph.demand[i] ? false : done;
    return done;
}

void do_case(std::istream& input) {
    auto graph = get_graph(input);

    int min_armies = INT32_MAX;
    for (auto& border_id : graph.borders) {
        min_armies = std::min(min_armies, graph.armies[border_id]);
    }
    for (auto& border_id : graph.borders) {
        graph.demand[border_id] = min_armies;
    }
    int max_armies = INT32_MAX;
    for (auto& border_id : graph.borders) {
        int army = graph.armies[border_id];
        for (auto connection : graph.connections[border_id]) {
            army += graph.armies[connection];
        }
        max_armies = std::min(max_armies, army);
    }

    auto old_graph = graph;
    int min = min_armies;
    int max = max_armies;
    while (min != max) {
        auto mid = min + (max - min + 1) / 2;
        for (auto& border_id : graph.borders) {
            graph.demand[border_id] = mid;
        }
        if (max_flow(graph)) {
            min = mid;
        } else {
            if (max == mid)
                max = min;
            else
                max = mid;
        }
        graph = old_graph;
    }
    std::cout << min << std::endl;
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
    for (int t = 0; t < T; t++)
        do_case(input);
}