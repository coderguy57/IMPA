#include <fstream>
#include <iostream>
#include <stdint.h>

#include <array>
#include <sstream>
#include <vector>

const int MAX_COL = 9;
struct Node
{
    int min;
    int min_index;
    int second_min;
    std::vector<int> childs;
};
std::vector<Node> nodes;
std::vector<int> parents;
int N;
void get_sum(int n) {
    for (int child : nodes[n].childs) {
        get_sum(child);
    }
    nodes[n].min = INT32_MAX;
    for (int i = 0; i < MAX_COL; i++) {
        int sum = i + 1;
        for (int child : nodes[n].childs) {
            if (i == nodes[child].min_index)
                sum += nodes[child].second_min;
            else
                sum += nodes[child].min;
        }
        if (nodes[n].min >= sum) {
            nodes[n].min_index = i;
            nodes[n].second_min = nodes[n].min;
            nodes[n].min = sum;
        } else if (nodes[n].second_min > sum) {
            nodes[n].second_min = sum;
        }
    }
}

void do_case(std::istream &input)
{
    if (N == 0)
        return;

    nodes.assign(N, Node{});
    parents.assign(N, -1);
    for (int n = 0; n < N; n++)
    {
        std::string line;
        int node;
        char c;
        input >> node >> c;
        std::getline(input, line);
        std::stringstream ss(line);
        int child;
        while (ss >> child) {
            nodes[node].childs.push_back(child);
            parents[child] = node;
        }
    }
    int parent = 0;
    while (parents[parent] != -1) {
        parent = parents[parent];
    }

    get_sum(parent);
    std::cout << nodes[parent].min << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (input >> N)
    {
        do_case(input);
    }
}