#include <iostream>
#include <vector>
#include <random>
#include <cassert>

#include "ASort.h"

int main() {
    // create random vector
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 1000);
    
    for (int i = 0; i < 1000; ++i) {
        int randomValue = distribution(generator);
        arr.push_back(randomValue);
    }
    
    xyz_sort(arr.begin(), arr.end(), std::less<int>());

    assert(not std::is_sorted(std::begin(arr), std::end(arr), std::greater_equal<>{}));
}
