#include <fstream>
#include <iostream>
#include <cstdint>

#include <map>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> stack;
std::map<std::vector<int>, int> map;

int get_id(std::vector<int> const& set) {
    auto it = map.find(set);
    if (it != map.end())
        return it->second;
    
    map[set] = map.size();
    return map.size() - 1;
}

void do_case(std::istream& input) {
    stack.clear();
    map.clear();

    int N;
    input >> N;
    for (int n = 0; n < N; n++) {
        std::string op;
        input >> op;

        if (op == "PUSH") {
            stack.push_back(std::vector<int>{});
        } else  if (op == "DUP") {
            stack.push_back(stack.back());
        } else {
            auto top1 = std::move(stack.back());
            stack.pop_back();
            auto top2 = std::move(stack.back());
            stack.pop_back();

            if (op == "UNION") {
                std::vector<int> v_union;
                std::set_union(top1.begin(), top1.end(), top2.begin(), top2.end(),
                                    std::back_inserter(v_union));
                std::sort(v_union.begin(), v_union.end());
                stack.emplace_back(std::move(v_union));
            } else if (op == "INTERSECT") {
                std::vector<int> v_intersection;
                std::set_intersection(top1.begin(), top1.end(), top2.begin(), top2.end(),
                                    std::back_inserter(v_intersection));
                std::sort(v_intersection.begin(), v_intersection.end());
                stack.emplace_back(std::move(v_intersection));
            } else if (op == "ADD") {
                auto id = get_id(top1);
                auto lower = std::lower_bound(top2.begin(), top2.end(), id);
                if (lower == top2.end() || *lower != id)
                    top2.insert(lower, id);
                stack.emplace_back(std::move(top2));
            }
        }
        std::cout << stack.back().size() << std::endl;
    }
    std::cout << "***" << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int T = 0;
    input >> T;
    for (int t = 0; t < T; t++)
    {
        do_case(input);
    }
}