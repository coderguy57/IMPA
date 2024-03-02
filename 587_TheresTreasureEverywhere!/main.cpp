#include <fstream>
#include <iostream>
#include <cstdint>

#include <vector>
#include <cmath>
#include <iomanip>

struct Point
{
    double x, y;
};

int parse_int(std::string &s, int &index)
{
    int result = 0;
    while (isdigit(s[index]))
    {
        result *= 10;
        result += s[index] - '0';
        index++;
    }
    return result;
}

bool move_position(Point& p, std::string &s, int& index)
{
    double distance = parse_int(s, index);
    Point direction = {0, 0};
    if (s[index] == 'N') {
        direction.y = 1;
        index++;
    } else if (s[index] == 'S') {
        direction.y = -1;
        index++;
    }
    if (s[index] == 'E') {
        direction.x = 1;
        index++;
    } else if (s[index] == 'W') {
        direction.x = -1;
        index++;
    }
    distance /= direction.x == 0 || direction.y == 0 ? 1.0f : std::sqrt(2.0);
    p.x += direction.x * distance;
    p.y += direction.y * distance;

    return s[index++] == ',';
}

bool do_case(std::istream &input, int map)
{
    std::string line;
    input >> line;
    if (line == "END")
        return false;
    
    Point p = {0, 0};
    int index = 0;
    while (move_position(p, line, index));

    double distance = sqrt(p.x * p.x + p.y * p.y);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Map #" << map << "\n";
    std::cout << "The treasure is located at (" << p.x << "," << p.y << ").\n";
    std::cout << "The distance to the treasure is " << distance << ".\n\n";

    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int map = 1;
    while (do_case(input, map++));
}