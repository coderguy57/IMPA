#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <bitset>

int do_set(std::istream& input) {
    int N, S, Q;
    input >> N >> S >> Q;

    std::queue<int> B[N];
    for (int i = 0; i < N; i++) {
        int Qi;
        input >> Qi;
        for (int j = 0; j < Qi; j++) {
            int id;
            input >> id;
            B[i].push(id);
        }
    }
    std::bitset<128> stations = {};
    for (int i = 0; i < N; i++)
        stations[i] = !B[i].empty();

    if (stations.none())
        return 0;

    int pos = 0;
    int time = 0;
    std::stack<int> carrier;
    while (stations.any() || carrier.size()) {
        while (carrier.size()) {
            if (carrier.top() == pos + 1) {
                carrier.pop();
                time++;
            } else if (B[pos].size() < Q) {
                B[pos].push(carrier.top());
                carrier.pop();
                time++;
            } else {
                break;
            }
        }

        while (B[pos].size() > 0 && carrier.size() < S) {
            carrier.push(B[pos].front());
            B[pos].pop();
            time++;
        }
        stations[pos] = !B[pos].empty();

        time += 2;
        pos = (pos + 1) % N;
    }

    return time - 2;
}

int main() {
    std::istream& input = std::cin;
    // std::ifstream input("input.txt");

    int T;
    input >> T;
    for (int t = 1; t <= T; t++) {
        std::cout << do_set(input) << std::endl;
    }
}