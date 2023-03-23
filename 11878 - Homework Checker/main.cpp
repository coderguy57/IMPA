#include <fstream>
#include <iostream>

#include <string>

// Returns false when there is no more test cases
int do_case(std::istream& input) {
    int n1, n2;
    char op, eq;
    std::string res;
    input >> n1 >> op >> n2 >> eq >> res;
    if (!input)
        return 0;
    if (res == "?")
        return 0;

    if (op == '+')
        return (n1 + n2) == std::stoi(res);
    else
        return (n1 - n2) == std::stoi(res);
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int correct = 0;
    while (input) {
        correct += do_case(input);
    }
    std::cout << correct << std::endl;
}