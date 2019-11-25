#include "util.hpp"

namespace {
template <typename T>
void swap(T* a, T* b)
{
    T t = *a;
    *a = *b;
    *b = t;
}

template <typename T>
int partition(T arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap<T>(&arr[i], &arr[j]);
        }
    }
    swap<T>(&arr[i+1], &arr[high]);
    return (i + 1);
}

template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition<T>(arr, low, high);
        quickSort<T>(arr, low, pi - 1);
        quickSort<T>(arr, pi + 1, high);
    }
}
}

template <typename T>
void quickSortBasline(T arr[], int start, int end) {
    quickSort<T>(arr, start, end - 1);
}