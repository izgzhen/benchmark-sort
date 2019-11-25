#include "util.hpp"

int main() {
    for (int n = 0; n < 1000000; n += 10000) {
        std::vector<float> nums = getRandList(n);
        Timer t;
        std::sort(nums.begin(), nums.end());
        std::cout << n << "\t" << t.GetDurationMicroseconds() << "\n";
    }
}