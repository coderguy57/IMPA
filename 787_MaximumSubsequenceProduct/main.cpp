#include <fstream>
#include <iostream>
#include <cstdint>

#include <cassert>
#include <vector>

// Simple large number struct that can handle arbitrary large numbers using a vector as base
struct large_number {
    std::vector<uint32_t> parts;
    bool negative;
    large_number(int n) : parts(1, std::abs(n)), negative{n < 0}  { }
    large_number() : parts(1, 0), negative{false} { }
    large_number(large_number const& other) : parts(other.parts), negative{other.negative} { }
    large_number operator*(const large_number& other) const {
        large_number result;
        result.negative = negative ^ other.negative;
        result.parts.resize(parts.size() + other.parts.size(), 0);
        for (int i = 0; i < parts.size(); i++) {
            for (int j = 0; j < other.parts.size(); j++) {
                auto part = uint64_t(parts[i]) * uint64_t(other.parts[j]);
                for (int k = 0; part > 0; k++) {
                    part += uint64_t(result.parts[i + j + k]);
                    result.parts[i + j + k] = uint32_t(part);
                    part >>= 32;
                }
            }
        }
        while (result.parts.size() > 1 && result.parts.back() == 0) {
            result.parts.pop_back();
        }
        return result;
    }
    large_number operator/(int32_t const& rhs) const {
        assert(rhs != 0);

        large_number result(*this);
        auto other = rhs;
        result.negative ^= (other < 0);
        other *= (other < 0)? -1 : 1;
        uint64_t carry = 0;
        for (int i = parts.size(); i --> 0;) {
            auto part = uint64_t(parts[i]);
            part += carry << 32;
            carry = part % other;
            result.parts[i] = uint32_t(part / other);
        }
        while (result.parts.size() > 1 && result.parts.back() == 0) {
            result.parts.pop_back();
        }
        return result;
    }
    int32_t operator%(int32_t const& rhs) const {
        assert(rhs != 0);

        large_number result(*this);
        auto other = rhs;
        result.negative ^= (other < 0);
        other *= (other < 0)? -1 : 1;
        uint64_t carry = 0;
        for (int i = parts.size(); i --> 0;) {
            auto part = uint64_t(parts[i]);
            part += carry << 32;
            carry = part % other;
            result.parts[i] = uint32_t(part / other);
        }
        return carry;
    }
    bool operator>(const large_number& other) const {
        if (negative != other.negative) {
            return !negative;
        }
        if (parts.size() != other.parts.size()) {
            return negative ^ (parts.size() > other.parts.size());
        }
        for (int i = parts.size() - 1; i >= 0; i--) {
            if (parts[i] != other.parts[i]) {
                return negative ^ (parts[i] > other.parts[i]);
            }
        }
        return false;
    }
    bool is_zero() const {
        return parts.size() == 1 && parts[0] == 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const large_number& n) {
        auto temp_number = large_number(n);

        std::vector<char> res;
        if (temp_number.negative)
            os << '-';
        if (temp_number.is_zero())
            return os << '0';
        while (!temp_number.is_zero()) {
            std::string s = std::to_string(temp_number % 10);
            for (int i = s.size(); i --> 0;)
                res.push_back(s[i]);
            for (int i = 0; i < 1 - s.size(); i++)
                res.push_back('0');

            temp_number = temp_number / 10;
        }
        int i = res.size() - 1;
        for (; i >= 0; i--) {
            if (res[i] != '0')
                break;
        }
        for (; i >= 0; i--) {
            os << res[i];
        }
        return os;
    }
};

bool do_case(std::istream& input) {
    int n;
    std::vector<int> numbers;
    while (input >> n && n != -999999) {
        numbers.push_back(n);
    }
    if (numbers.empty()) {
        return false;
    }

    large_number maximum = numbers[0];
    large_number cur_max = numbers[0];
    large_number cur_min = numbers[0];
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] < 0) {
            std::swap(cur_max, cur_min);
        }
        auto cur_num = large_number(numbers[i]);
        cur_max = cur_max * cur_num;
        cur_min = cur_min * cur_num;

        cur_max = cur_max > cur_num? cur_max : cur_num;
        cur_min = cur_num > cur_min? cur_min : cur_num;
        maximum = maximum > cur_max? maximum : cur_max;
    }

    std::cout << maximum << std::endl;
    return true;
}

int main()
{
#ifdef ONLINE_JUDGE
    std::istream &input = std::cin;
#else
    std::ifstream input("input.txt");
#endif

    int i = 1;
    while(do_case(input)) { 
        i++;
    }
}