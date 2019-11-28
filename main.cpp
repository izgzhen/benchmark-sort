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
    int interval = read<int>(argv[2]);
    int max_n = read<int>(argv[3]);
    std::string dist_opt(argv[4]);
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
    for (int n = interval; n < max_n; n += interval) {
        std::vector<int> nums;
        if (dist_opt == "uniform-random") {
            nums = getRandIntList(n);
        } else if (dist_opt == "reversed") {
            nums = getReversedIntList(n);
        } else {
            std::cerr << "Invalid dist_opt: " << dist_opt << "\n";
            exit(-1);
        }
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