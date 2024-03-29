#pragma once
#include <algorithm>
#include <sstream>
#include <iostream>
#include <climits>
#include <vector>
#include "assert.h"
#include <chrono>
#include <random>
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

std::vector<int> getRandIntList(int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, INT_MAX);

    std::vector<int> ret;
    for (int i = 0; i < N; i++) {
        ret.push_back(dis(gen));
    }
    return ret;
}

std::vector<int> getReversedIntList(int N) {
    std::vector<int> ret;
    for (int i = 0; i < N; i++) {
        ret.push_back(N - i);
    }
    return ret;
}

template <class T>
static T read(const char* value) {
    std::istringstream stream(value);
    T out;
    stream >> out;
    return out;
}
