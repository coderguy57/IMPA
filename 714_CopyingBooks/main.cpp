#include <fstream>
#include <iostream>
#include <cstdint>

#include <algorithm>
#include <tuple>

#include <vector>

void do_case(std::istream &input) {
    uint64_t k, m;
    input >> m >> k;

    std::vector<uint64_t> books(m);
    for (uint64_t i = 0; i < m; i++)
        input >> books[i];

    auto max = std::max_element(books.begin(), books.end());
    uint64_t left= *max, right = (*max) * m;
    while (left < right) {
        uint64_t mid = (left + right) / 2;
        uint64_t pages = books[m-1];
        int people = k-1;
        for (int i = m-2; i >= 0; i--) {
            if (pages + books[i] <= mid) {
                pages += books[i];
            } else {
                if (--people < 0) break;
                pages = books[i];
            }
        }
        if (people >= 0) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    std::vector<int> book_indices(k, 0);
    {
        uint64_t pages = books[m-1];
        int people = k-1;
        for (int i = m-2; i >= 0; i--) {
            if (pages + books[i] <= left && i >= people) {
                pages += books[i];
            } else {
                book_indices[people--] = i;
                if (people < 0) break;
                pages = books[i];
            }
        }
    }

    int people = 1;
    for (int i = 0; i < m; i++) {
        std::cout << books[i];
        if (i < m-1) std::cout << " ";
        if (i == book_indices[people]) {
            std::cout << "/ ";
            people++;
        }
    }
    std::cout << "\n";
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
    {
        do_case(input);
    }
}