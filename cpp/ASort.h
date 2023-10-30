#ifndef ASort_h
#define ASort_h
#include <iostream>

template<class RandomAccessIterator, class Less>
void xyz_sort(RandomAccessIterator first, RandomAccessIterator beyond, Less less) {
    RandomAccessIterator mut_beyond = beyond;
    bool swapped;
    do {
        swapped = false;
        for (RandomAccessIterator i = first; i != mut_beyond - 1; ++i) {
            if(!less(*i, *(i + 1))) {
                std::iter_swap(i, i + 1);
                swapped = true;
            }
        }
        mut_beyond--;
    }while ( swapped );
 }

#endif
