#include <iostream>
#include <vector>
#include <random>
#include <cassert>

#include "ASort.hpp"

#define SIZE 100

// #define _DEBUG

int main()
{
    // create random vector
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    arr.push_back(distribution(generator) + 1);

    for (int i = 1; i < SIZE; ++i)
    {
        int randomValue = arr[i - 1] + (distribution(generator) - distribution(generator) / 2);
        arr.push_back(randomValue);
    }

    std::vector<int> arr_out(SIZE);

    CKA::sort(arr.begin(), arr.end(), arr_out.begin(), std::less<int>());
    CKA::sort(arr.begin(), arr.end(), std::less<int>());

    std::cout << "First isSorted: "
              << std::is_sorted(std::begin(arr_out), std::end(arr_out))
              << "\nSecond isSorted: "
              << std::is_sorted(std::begin(arr), std::end(arr))
              << std::endl;

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
