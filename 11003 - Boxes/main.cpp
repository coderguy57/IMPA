#include <fstream>
#include <iostream>

#include <array>

// The max loads that can be put
std::array<int32_t, 3000> loads;

// Returns false when there is no more test cases
bool do_case(std::istream& input) {
    int N;
    input >> N;
    if (N == 0)
        return false;
    
    // Initalize the max loads
    std::fill(loads.begin(), loads.begin() + N + 1, -1);
    loads[0] = INT32_MAX;

    int top_box = 0;
    for (int i = 0; i < N; i++) {
        int W, L;
        input >> W >> L;
        for (int j = top_box + 1; loads[j] < L; j--) {
            loads[j] = std::max(std::min(loads[j - 1] - W, L), loads[j]);
        }
        if (loads[top_box+1] != -1)
            top_box++;
    }
    
    std::cout << top_box << std::endl;

    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (true) {
        if (!do_case(input))
            return 0;
    }
}