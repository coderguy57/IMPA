#include <fstream>
#include <iostream>
#include <cstdint>

#include <unordered_map>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

void load_line(std::vector<std::string>& result, std::istream &input)
{
    std::string line;
    std::getline(input, line);
    std::istringstream iss(line);
    std::string token;
    while (iss >> token)
    {
        result.push_back(token);
    }
}

bool is_placeholder(std::string& value) {
    return value[0] == '<';
}

struct node
{
    node* pointer = nullptr;
    std::string value = "";
    node() {}
    node(std::string v) : value{v} {}
    node(std::string v, node& n) : pointer{&n} {}
};

node& get_node(node& in) {
    node* out = &in;
    node* prev = &in;
    while (out->pointer) {
        prev->pointer = out->pointer;
        prev = out;
        out = out->pointer;
    }
    return *out;
}

bool one_placeholder(
    std::unordered_map<std::string, node>& placeholders, 
    std::string& token, 
    std::string& other_token) 
{
    if (placeholders.count(token)) {
        auto& node = get_node(placeholders[token]);
        if (node.value == "")
            node.value = other_token;
        else if (node.value != other_token)
            return false;
    } else {
        placeholders.insert(std::make_pair(token, node(other_token)));
    }
    return true;
}

std::unordered_map<std::string, node> placeholderA;
std::unordered_map<std::string, node> placeholderB;
std::vector<std::string> tokensA;
std::vector<std::string> tokensB;
std::string do_case(std::istream &input)
{
    placeholderA.clear();
    placeholderB.clear();
    tokensA.clear();
    tokensB.clear();
    load_line(tokensA, input);
    load_line(tokensB, input);

    if (tokensA.size() != tokensB.size())
        return "-";

    for (int i = 0; i < tokensA.size(); i++)
    {
        auto& tokenA = tokensA[i];
        auto& tokenB = tokensB[i];
        if (is_placeholder(tokenA) && !is_placeholder(tokenB)) {
            if (!one_placeholder(placeholderA, tokenA, tokenB))
                return "-";
        } else if (!is_placeholder(tokenA) && is_placeholder(tokenB)) {
            if (!one_placeholder(placeholderB, tokenB, tokenA))
                return "-";
        } else if (is_placeholder(tokenA) && is_placeholder(tokenB)) {
            if (placeholderA.count(tokenA) && placeholderB.count(tokenB)) {
                auto& nodeA = get_node(placeholderA[tokenA]);
                auto& nodeB = get_node(placeholderB[tokenB]);
                if (&nodeA == &nodeB)
                    continue;
                if (nodeA.value != "" && nodeB.value != "" && nodeA.value != nodeB.value)
                    return "-";
                if (nodeA.value == "") {
                    nodeA.value = "";
                    nodeA.pointer = &nodeB;
                } else {
                    nodeB.value = "";
                    nodeB.pointer = &nodeA;
                }
            } else if (placeholderA.count(tokenA) && !placeholderB.count(tokenB)) {
                auto& nodeA = get_node(placeholderA[tokenA]);
                placeholderB.insert({tokenB, node("", nodeA)});
            } else if (!placeholderA.count(tokenA) && placeholderB.count(tokenB)) {
                auto& nodeB = get_node(placeholderB[tokenB]);
                placeholderA.insert({tokenA, node("", nodeB)});
            } else {
                placeholderA.insert({tokenA, node("")});
                placeholderB.insert({tokenB, node("", placeholderA[tokenA])});
            }
        } else {
            if (tokenA != tokenB)
                return "-";
        }
    }

    std::string result = "";
    for (int i = 0; i < tokensA.size(); i++)
    {
        auto& tokenA = tokensA[i];
        if (is_placeholder(tokenA)) {
            auto& value = get_node(placeholderA[tokenA]).value;
            result += value == "" ? "tomek" : value;
        } else {
            result += tokenA;
        }
        result += i + 1 < tokensA.size() ? " " : "";
    }
    return result;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int N = 0;
    std::string temp;
    input >> N;
    std::getline(input, temp);
    for (int n = 0; n < N; n++)
    {
        std::cout << do_case(input) << std::endl;
    }
}