#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <algorithm>

struct Light
{
    Light() = default;
    Light(int x, int y, int z) : x{x}, y{y}, z{z}
    {
        angle = std::atan2(y, x);
        distance = static_cast<uint64_t>(x) * x + static_cast<uint64_t>(y) * y;
    }
    double angle;
    uint64_t distance;
    int x, y, z;
};

struct LightComparator
{
    bool operator()(const Light &a, const Light &b)
    {
        return a.angle < b.angle || (a.angle == b.angle && a.distance < b.distance);
    }
};

struct NonVisibleComparator
{
    std::vector<Light> &lights;
    bool operator()(int a, int b)
    {
        return lights[a].x < lights[b].x || (lights[a].x == lights[b].x && lights[a].y < lights[b].y);
    }
};

void do_case(std::istream &input, int N, int dataset)
{
    std::vector<Light> lights(N);
    for (int i = 0; i < N; i++)
    {
        int x, y, z;
        input >> x >> y >> z;
        lights[i] = Light(x, y, z);
    }

    std::sort(lights.begin(), lights.end(), LightComparator());

    std::vector<int> not_visible;
    int max_height = lights[0].z;
    for (int i = 1; i < N; i++)
    {
        if (lights[i].angle == lights[i - 1].angle)
        {
            if (lights[i].z <= max_height)
            {
                not_visible.push_back(i);
            }
            else
            {
                max_height = lights[i].z;
            }
        }
        else
        {
            max_height = lights[i].z;
        }
    }
    std::sort(not_visible.begin(), not_visible.end(), NonVisibleComparator{lights});

    std::cout << "Data set " << dataset << ":\n";
    if (not_visible.size() == 0)
    {
        std::cout << "All the lights are visible.\n";
    }
    else
    {
        std::cout << "Some lights are not visible:\n";
        for (int i = 0; i < not_visible.size(); i++)
        {
            std::cout << "x = " << lights[not_visible[i]].x << ", y = " << lights[not_visible[i]].y;
            if (i + 1 == not_visible.size())
                std::cout << ".\n";
            else
                std::cout << ";\n";
        }
    }
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int dataset = 1;
    int N;
    while (input >> N && N != 0)
    {
        do_case(input, N, dataset++);
    }
}