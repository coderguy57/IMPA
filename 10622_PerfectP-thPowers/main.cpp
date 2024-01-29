#include <fstream>
#include <iostream>
#include <cstdint>

#include <cmath>

int64_t pow(int64_t x, unsigned int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;
  
  auto tmp = pow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}

void do_case(int64_t n) {
    bool negative = n < 0;
    n *= negative ? -1 : 1;

    double d = n;

    int64_t largerst_p = 1;
    for (int p = 2;; p++) {
        int64_t root = std::round(std::pow(d, 1.0 / p));
        if (pow(root, p) == n) {
            if (!negative || p % 2 == 1)
                largerst_p = p;
        }
        
        if (root < 2)
            break;
    }

    std::cout << largerst_p << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int n;
    while (input >> n && n != 0) {
        do_case(n);
    }
}