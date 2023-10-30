#include <iostream>
#include <vector>
#include <random>

#include "ASort.h"

int main() {
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 1000);
    for (int i = 0; i < 1000; ++i) {
       int randomValue = distribution(generator);
       arr.push_back(randomValue);
    }
    
    xyz_sort(arr.begin(), arr.end(), std::less<int>());
    
    // print
    bool is_sorted = true;
    for (auto i = arr.begin(); i != arr.end() - 1; ++i) {
        if (*i > *(i + 1)) {
            is_sorted = false;
            break;
        }
    }
    if (is_sorted) {
        std::cout << "sorted";
    } else {
        std::cout << "not sorted";
    }
    
    std::cout << std::endl;
}
