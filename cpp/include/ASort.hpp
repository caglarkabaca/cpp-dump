#ifndef ASort_h
#define ASort_h

#include <vector>

namespace CKA
{
    // it is classic merge sort with sortness checking before
    template <class RandomAccessIterator, class Less>
    void sort(RandomAccessIterator first, RandomAccessIterator beyond, Less less)
    {
        bool is_sorted = true;
        for (RandomAccessIterator i = first; i != beyond - 1; ++i)
        { // checks if the array already sorted in right way
            if (!less(*i, *(i + 1)))
            {
                is_sorted = false;
                break;
            }
        }

        if (is_sorted)
            return;

        bool is_sorted_in_reverse = true;
        for (RandomAccessIterator i = first; i != beyond - 1; ++i)
        { // checks if the array already sorted in reverse way
            if (less(*i, *(i + 1)))
            {
                is_sorted_in_reverse = false;
                break;
            }
        }

        if (is_sorted_in_reverse)
        {
            std::reverse(first, beyond);
            return;
        }

        int size = std::distance(first, beyond);
        if (size < 2)
            return;

        RandomAccessIterator middle = std::next(first, size / 2);

        CKA::sort(first, middle, less);
        CKA::sort(middle, beyond, less);

        // merge()
        std::vector<typename RandomAccessIterator::value_type> arr;
        RandomAccessIterator l{first}, r{middle};
        const RandomAccessIterator im_middle{middle}, im_beyond{beyond};

        while (l != im_middle && r != im_beyond)
        {
            if (!less(*r, *l))
            {
                arr.push_back(*(l++));
                continue;
            }
            arr.push_back(*(r++));
        }

        while (l != im_middle)
            arr.push_back(*(l++));

        while (r != im_beyond)
            arr.push_back(*(r++));

        RandomAccessIterator i_arr = arr.begin();
        for (RandomAccessIterator i = first; i != beyond; ++i)
            std::iter_swap(i, i_arr++);
    }

    template <class InputIterator, class OutputIterator, class Less>
    OutputIterator sort(InputIterator first, InputIterator beyond, OutputIterator result, Less less)
    {
        std::vector<typename InputIterator::value_type> random_arr;
        std::copy(first, beyond, std::back_inserter(random_arr));
        CKA::sort(random_arr.begin(), random_arr.end(), less);

        for (auto i = random_arr.begin(); i != random_arr.end(); ++i)
        {
            *(result++) = *i;
        }
        return result;
    }
}

#endif
