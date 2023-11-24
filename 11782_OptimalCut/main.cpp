#include <fstream>
#include <iostream>
#include <stdint.h>

#include <memory>
#include <vector>

template<typename T>
class span {
   T* ptr_;
   std::size_t len_;

public:
    span(T* ptr, std::size_t len) noexcept
        : ptr_{ptr}, len_{len}
    {}

    T& operator[](int i) noexcept {
        return ptr_[i];
    }

    T const& operator[](int i) const noexcept {
        return ptr_[i];
    }

    std::size_t size() const noexcept {
        return len_;
    }

    T* begin() noexcept {
        return ptr_;
    }

    T* end() noexcept {
        return ptr_ + len_;
    }
};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct Node {
    std::unique_ptr<Node> l = nullptr;
    std::unique_ptr<Node> r = nullptr;
    int weight;

    Node(span<int> weights, int depth) {
        weight = weights[0];
        if (depth > 0) {
            int tree_size = (1 << depth) - 1;
            l = make_unique<Node>(span<int>(&weights[1], tree_size), depth - 1);
            r = make_unique<Node>(span<int>(&weights[1 + tree_size], tree_size), depth - 1);
        }
    }
    void print() {
        printf("%d ", weight);
        if (l) {
            l->print();
            r->print();
        }
    }
    std::vector<int> calc(int max_cuts) {
        if (!l)
            return std::vector<int>{weight};
        
        auto l_cuts = l->calc(max_cuts);
        auto r_cuts = r->calc(max_cuts);
        std::vector<int> cuts(std::min<int>(l_cuts.size() * 2, max_cuts), INT_LEAST32_MIN);
        cuts[0] = weight;
        for (int i = 0; i < l_cuts.size(); i++) {
            for (int j = 0; j < r_cuts.size(); j++) {
                if (i + j + 1 < max_cuts)
                    cuts[i + j + 1] = std::max(l_cuts[i] + r_cuts[j], cuts[i + j + 1]);
            }
        }
        return cuts;
    }
};

bool do_case(std::istream &input) {
    int H, K;
    input >> H >> K;
    if (H == -1)
        return false;
    int tree_size = (1 << (H + 1)) - 1;
    std::vector<int> weights(tree_size);
    for (int i = 0; i < tree_size; i++) { 
        input >> weights[i];
    }
    auto node = Node(span<int>(&weights[0], tree_size), H);
    auto cuts = node.calc(K);
    int opt_cut = cuts[0];
    for (int i = 1; i < cuts.size(); i++)
        opt_cut = std::max(opt_cut, cuts[i]);
    printf("%d\n", opt_cut);

    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (do_case(input))
    {
    }
}