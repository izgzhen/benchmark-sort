#include "util.hpp"
#include "quicksort.hpp"

enum ALGO {
    STDSORT,
    QSORT,
    QSORT_BASELINE
};

int compare_int(const void *a, const void *b) {
    return ( *(int*)a -  *(int*)b );
}

int main(int argc, char* argv[]) {
    std::string algo_opt(argv[1]);
    ALGO algo;
    if (algo_opt == "stdsort") {
        algo = STDSORT;
    } else if (algo_opt == "qsort") {
        algo = QSORT;
    } else if (algo_opt == "qsort-baseline") {
        algo = QSORT_BASELINE;
    } else {
        std::cerr << "Invalid algo_opt: " << algo_opt << "\n";
        exit(-1);
    }
    for (int n = 10000; n < 1000000; n += 10000) {
        // std::vector<float> nums = getRandList(n);
        std::vector<int> nums = getRandIntList(n);
        Timer t;
        switch (algo) {
            case STDSORT:
                std::sort(nums.begin(), nums.end());
                break;
            case QSORT:
                qsort(&nums[0], nums.size(), sizeof(int), compare_int);
                break;
            case QSORT_BASELINE:
                quickSortBasline<int>(nums.data(), 0, nums.size());
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