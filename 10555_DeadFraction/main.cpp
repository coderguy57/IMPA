#include <fstream>
#include <iostream>
#include <cstdint>

#include <climits>

int64_t gcd(int64_t a, int64_t b) 
{ 
    if (a % b == 0) 
        return b;
    else
        return gcd(b, a % b);
} 

int64_t pow(int64_t x, unsigned int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;
  
  auto tmp = pow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}

struct Fraction {
    int64_t n; // Numerator
    int64_t d; // Denominator

    void simplify() {
        auto divisor = gcd(n, d);
        d /= divisor;
        n /= divisor;
    }

    Fraction(int64_t numerator, int64_t denomiator) 
        : n{numerator}, d{denomiator} {
        simplify();
    }

    Fraction& operator+=(const Fraction& rhs)
    {
        n = n * rhs.d + rhs.n * d;
        d *= rhs.d;
        simplify();
        return *this;
    }

    friend Fraction operator+(Fraction lhs, const Fraction& rhs)
    {
        lhs += rhs;
        return lhs;
    }
};

void do_case(std::string n) {
    std::string decimals(n.begin() + 2, n.end() - 3);    

    Fraction min_den(1, LONG_MAX);
    for (int i = decimals.size(); i --> 0;) {
        std::string repeating_decimals(decimals.begin() + i, decimals.end());
        std::string other_decimals(decimals.begin(), decimals.begin() + i);
        Fraction fraction(0, 1);
        int64_t denominator = 1;
        if (other_decimals.size()) {
            auto oth_dec = std::stol(other_decimals);
            denominator = pow(10, other_decimals.size());
            fraction = Fraction(oth_dec, denominator);
        }
        denominator *= (pow(10, repeating_decimals.size()) - 1);
        fraction += Fraction(std::stol(repeating_decimals), denominator);
        if (fraction.d < min_den.d)
            min_den = fraction;
    }
    std::cout << min_den.n << "/" << min_den.d << std::endl;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    std::string n;
    while (input >> n && n != "0") {
        do_case(n);
    }
}