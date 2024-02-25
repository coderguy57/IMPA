#include <fstream>
#include <iostream>

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>

std::unordered_map<uint32_t, int> map;
void generete_fibonacci()
{
    uint32_t prev = 0;
    uint32_t curr = 1;
    int index = 0;
    while (prev + curr >= curr)
    {
        map.emplace(prev + curr, index);
        index++;
        auto temp = curr;
        curr = prev + curr;
        prev = temp;
    }
}

void clear_line() {
    char c;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int indices[10001];
std::array<char, 10001> output;
void do_case()
{
    int N;
    scanf("%d", &N);

    int max = -1;
    for (int i = 0; i < N; i++)
    {
        uint32_t num;
        scanf("%u", &num);
        int index = map.at(num);
        max = std::max(index, max);
        indices[i] = index;
    }
    clear_line();

    for (int i = 0; i < max + 1; i++)
        output[i] = ' ';

    for (int i = 0; i < N;)
    {
        char c = getchar();
        if (c == '\n' || c == EOF) break;
        if (!isalpha(c))
            continue;
        if (islower(c))
            continue;
        int index = indices[i++];
        output[index] = c;
    }
    clear_line();
    output[max+1] = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    generete_fibonacci();

    int T = 0;
    scanf("%d", &T);
    for (int t = 0; t < T; t++)
    {
        do_case();
        printf("%s\n", output.data());
    }
}