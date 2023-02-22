#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

std::unordered_map<std::string, int> city_to_id;
std::vector<std::string> cities;
std::vector<std::string> route_names;

struct Edge {
    constexpr Edge(int dist, int to, int name_id) : dist{dist}, to{to}, name_id{name_id} { }
    int dist;
    int to;
    int name_id;
};
std::vector<std::vector<Edge>> edges;

std::string get_next(std::string const& string, int &pos) {
    int next = string.find(',', pos);
    std::string out = string.substr(pos, next - pos);
    pos = next + 1;
    return out;
}

int get_id_from_city(std::string const& city) {
    auto search = city_to_id.find(city);
    if (search != city_to_id.end())
        return search->second;
    
    cities.push_back(city);
    city_to_id[city] = city_to_id.size();
    edges.push_back({});
    return city_to_id.size() - 1;
}

void get_route(std::string const& s) {
    int pos = 0;

    int city_id1 = get_id_from_city(get_next(s, pos));
    int city_id2 = get_id_from_city(get_next(s, pos));
    route_names.push_back(get_next(s, pos));
    int dist = std::stoi(get_next(s, pos));

    if (city_id2 < city_id1)
        std::swap(city_id1, city_id2); 

    auto search = std::find_if(edges[city_id1].begin(), edges[city_id1].end(), [city_id2](Edge const& edge) {
        return edge.to == city_id2;
    });
    if (search == edges[city_id1].end()) {
        edges[city_id1].emplace_back(dist, city_id2, route_names.size() - 1);
    } else {
        if (search->dist > dist) {
            // Change the distance if it's lower
            search->dist = dist;
            search->name_id = route_names.size() - 1;
        }
    }
}

struct Vertex {
    constexpr Vertex(int dist, int to, int from) : dist{dist}, to{to}, from{from} { }
    int dist;
    int to;
    int from;
};
std::vector<uint32_t> dist;
std::vector<int> backtrack;
void calc(int start, int end) {
    struct customLess
    {
        bool operator() (const Vertex& a, const Vertex& b) const { return a.dist > b.dist; }
    };
    std::priority_queue<Vertex, std::vector<Vertex>, customLess> heap;
    heap.emplace(0, start, -1);
    dist.assign(city_to_id.size(), -1);
    backtrack.assign(city_to_id.size(), -1);
    while (!heap.empty()) {
        auto vertex = heap.top();
        heap.pop();
        if (vertex.dist < dist[vertex.to]) {
            dist[vertex.to] = vertex.dist;
            backtrack[vertex.to] = vertex.from;
            if (vertex.to == end)
                break;

            for (auto& edge : edges[vertex.to]) {
                if(vertex.dist + edge.dist < dist[edge.to])
                    heap.emplace(vertex.dist + edge.dist, edge.to, vertex.to);
            }
        }
    }
}

void report(std::string input) {
    int pos = 0;

    int start_city = get_id_from_city(get_next(input, pos));
    int end_city = get_id_from_city(get_next(input, pos));

    calc(start_city, end_city);

    std::cout << "\n\n";
    std::cout << "From                 To                   Route      Miles" << '\n';
    std::cout << "-------------------- -------------------- ---------- -----" << '\n';
    int city = end_city;

    std::vector<int> queue;
    while (backtrack[city] != -1) {
        queue.push_back(city);
        city = backtrack[city];
    }
    queue.push_back(city);
    
    int total = 0;
    for (int i = queue.size(); i --> 1;) {
        int from_city_id = queue[i];
        int to_city_id = queue[i-1];

        auto& from_city = cities[from_city_id];
        std::cout << from_city << std::string(21 - from_city.size(), ' ');
        auto& to_city = cities[to_city_id];
        std::cout << to_city << std::string(21 - to_city.size(), ' ');

        auto search = std::find_if(edges[from_city_id].begin(), edges[from_city_id].end(), [to_city_id](Edge const& edge) {
            return edge.to == to_city_id;
        });
        auto& route_name = route_names[search->name_id];
        std::cout << route_name << std::string(11 - route_name.size(), ' ');
        std::string miles_str = std::to_string(search->dist); 
        std::cout << std::string(5 - miles_str.size(), ' ') << miles_str << '\n';

        total += search->dist;
    }
    std::cout << "                                                     -----" << '\n';
    std::cout << "                                          Total";
    std::string total_str = std::to_string(total); 
    std::cout << std::string(11 - total_str.size(), ' ') << total_str << '\n';
}

int main() {
    // std::ifstream input("input.txt");
    std::istream& input = std::cin;

    std::string line;
    while(getline(input, line), !line.empty()) {
        get_route(line);
    }
    for (int i = edges.size(); i --> 0;) {
        for (int j = edges[i].size(); j --> 0;) {
            auto& edge = edges[i][j]; 
            if (i < edge.to)
                edges[edge.to].emplace_back(edge.dist, i, edge.name_id);
        }
    }
    while(getline(input, line), !line.empty() && input) {
        report(line);
    }
}