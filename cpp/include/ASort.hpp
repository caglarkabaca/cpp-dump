#ifndef ASort_h
#define ASort_h

#include <vector>

namespace CKA
{
    template <class RandomAccessIterator, class Less>
    void xyz_sort(RandomAccessIterator first, RandomAccessIterator beyond, Less less)
    {
        int size = std::distance(first, beyond);
        if (size < 2)
            return;

        RandomAccessIterator middle = std::next(first, size / 2);

        xyz_sort(first, middle, less);
        xyz_sort(middle, beyond, less);

        // merge()
        std::vector<typename RandomAccessIterator::value_type> arr;
        RandomAccessIterator l{first}, r{middle};
        const RandomAccessIterator im_middle{middle}, im_beyond{beyond};

        while (l != im_middle && r != im_beyond)
        {
            if (!less(*r, *l))
            {
                arr.push_back(*(l++));
            }
            else
            {
                arr.push_back(*(r++));
            }
        }

        while (l != im_middle)
        {
            arr.push_back(*(l++));
        }

        while (r != im_beyond)
        {
            arr.push_back(*(r++));
        }

        RandomAccessIterator i_arr = arr.begin();
        for (RandomAccessIterator i = first; i != beyond; ++i)
        {
            std::iter_swap(i, i_arr++);
        }
    }

    template <class InputIterator, class OutputIterator, class Less>
    OutputIterator xyz_sort(InputIterator first, InputIterator beyond, OutputIterator result, Less less)
    {
        std::vector<typename InputIterator::value_type> random_arr;
        std::copy(first, beyond, std::back_inserter(random_arr));
        xyz_sort(random_arr.begin(), random_arr.end(), less);

        const OutputIterator c_result = result;
        for (auto i = random_arr.begin(); i != random_arr.end(); ++i)
        {
            *(result++) = *i;
        }
        return c_result;
    }
}

#endif
