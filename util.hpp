#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include "stdlib.h"

using namespace std::chrono;
class Timer {
public:
    Timer() : t_(high_resolution_clock::now()) {}

    double GetDurationMicroseconds() {
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(t2 - t_).count();
        return float(duration) / 1000.0;
    }

private:
    high_resolution_clock::time_point t_;
};

std::vector<float> getRandList(int N) {
    std::vector<float> ret;
    for (int i = 0; i < N; i++) {
        ret.push_back((float)rand() / (float)RAND_MAX);
    }
    return ret;
}
