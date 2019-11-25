#include "util.hpp"

enum ALGO {
    STDSORT,
    QSORT
};

int compare_float(const void *a, const void *b) {
    float delta = ( *(float*)b -  *(float*)a );
    if (delta > 0) {
        return -1;
    } else if (delta < 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char* argv[]) {
    std::string algo_opt(argv[1]);
    ALGO algo;
    if (algo_opt == "stdsort") {
        algo = STDSORT;
    } else if (algo_opt == "qsort") {
        algo = QSORT;
    } else {
        std::cerr << "Invalid algo_opt: " << algo_opt << "\n";
        exit(-1);
    }
    for (int n = 0; n < 1000000; n += 10000) {
        std::vector<float> nums = getRandList(n);
        Timer t;
        switch (algo) {
            case STDSORT:
                std::sort(nums.begin(), nums.end());
                break;
            case QSORT:
                qsort(&nums[0], nums.size(), sizeof(float), compare_float);
                break;
            default:
                std::cerr << "Sort not implemented: " << algo << "\n";
                exit(-1);
        }
        std::cout << n << "\t" << t.GetDurationMicroseconds() << "\n";

        // sanity check...
        for (int i = 0; i < n - 1; i++) {
            assert(nums[i] <= nums[i+1]);
        }
    }
}