#include <iostream>
#include <vector>
#include <random>
#include <cassert>

#include "ASort.h"

#define SIZE 15

#define _DEBUG

int main()
{
    // create random vector
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 1000);

    for (int i = 0; i < SIZE; ++i)
    {
        int randomValue = distribution(generator);
        arr.push_back(randomValue);
    }

    std::vector<int> arr_out(SIZE);

    xyz_sort(arr.begin(), arr.end(), arr_out.end(), std::less<int>());
    xyz_sort(arr.begin(), arr.end(), std::less<int>());

    assert(not std::is_sorted(std::begin(arr_out), std::end(arr_out), std::greater_equal<>{}));
    assert(not std::is_sorted(std::begin(arr), std::end(arr), std::greater_equal<>{}));
    std::cout << "Sorted" << std::endl;

#ifdef _DEBUG
    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    for (auto i = arr_out.begin(); i != arr_out.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
#endif
}
