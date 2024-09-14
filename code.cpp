#include <iostream>
#include <vector>
#include <functional>

// Constants for comparison
enum Compare {
    LESS_THAN = -1,
    BIGGER_THAN = 1
};

// Default comparison function
int defaultCompare(int a, int b) {
    if (a == b) {
        return 0;
    }
    return a < b ? Compare::LESS_THAN : Compare::BIGGER_THAN;
}

// Structure to hold swap positions
struct Swap {
    int firstPosition;
    int lastPosition;
};

std::vector<Swap> swaps;

// Partition function for QuickSort
int partition(std::vector<int>& array, int left, int right, std::function<int(int, int)> compareFn) {
    int pivot = array[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (compareFn(array[i], pivot) == Compare::LESS_THAN) {
            i++;
        }
        while (compareFn(array[j], pivot) == Compare::BIGGER_THAN) {
            j--;
        }
        if (i <= j) {
            std::swap(array[i], array[j]);
            swaps.push_back({i, j});
            i++;
            j--;
        }
    }

    return i;
}

// QuickSort function
void quick(std::vector<int>& array, int left, int right, std::function<int(int, int)> compareFn) {
    if (left < right) {
        int index = partition(array, left, right, compareFn);
        if (left < index - 1) {
            quick(array, left, index - 1, compareFn);
        }
        if (index < right) {
            quick(array, index, right, compareFn);
        }
    }
}

// SortingAlgorithms class
class SortingAlgorithms {
public:
    std::vector<Swap> bubbleSort(std::vector<int>& array) {
        swaps.clear();
        for (size_t i = 0; i < array.size(); i++) {
            for (size_t j = 0; j < array.size() - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                    swaps.push_back({static_cast<int>(j), static_cast<int>(j + 1)});
                }
            }
        }
        return swaps;
    }

    std::vector<Swap> selectionSort(std::vector<int>& array) {
        swaps.clear();
        for (size_t i = 0; i < array.size() - 1; i++) {
            size_t min = i;
            for (size_t j = i + 1; j < array.size(); j++) {
                if (array[j] < array[min]) {
                    min = j;
                }
            }
            std::swap(array[min], array[i]);
            swaps.push_back({static_cast<int>(min), static_cast<int>(i)});
        }
        return swaps;
    }

    std::vector<Swap> quickSort(std::vector<int>& array, std::function<int(int, int)> compareFn = defaultCompare) {
        swaps.clear();
        quick(array, 0, array.size() - 1, compareFn);
        return swaps;
    }
};

int main() {
    SortingAlgorithms sa;

    std::vector<int> array = {5, 3, 8, 4, 2};

    std::vector<Swap> bubbleSwaps = sa.bubbleSort(array);
    std::vector<Swap> selectionSwaps = sa.selectionSort(array);
    std::vector<Swap> quickSwaps = sa.quickSort(array);

    // Output swaps or sorted array as needed
    return 0;
}
