#include <fstream>
#include <iostream>
#include <cstdint>

bool do_case(std::istream &input)
{
    int H, U, D, F;
    input >> H >> U >> D >> F;
    if (H == 0)
    {
        return false;
    }
    double progress = 0;
    for (int day = 1;; day++)
    {
        double distance = U * (1 - (day - 1) * (F / 100.0));
        if (distance > 0)
        {
            progress += distance;
            if (progress > H)
            {
                std::cout << "success on day " + std::to_string(day) << std::endl;
                break;
            }
        }
        progress -= D;
        if (progress < 0)
        {
            std::cout << "failure on day " + std::to_string(day) << std::endl;
            break;
        }
    }
    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    while (do_case(input));
}