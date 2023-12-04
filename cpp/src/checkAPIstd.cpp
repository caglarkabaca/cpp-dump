// ======================================================================
//
// Copyright (c) OVGU Magdeburg
//
// This software and related files are part of an Algorithm Engineering
// implementation project on adaptive sorting of polygon vertices,
// conducted at computer science department (FIN) at OVGU Magdeburg,
// Germany. All rights reserved.
//
// version 1.1 - Nov 16, 2023
//
// ======================================================================

#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <Point_2.h>

#include <CKA.hpp>

typedef AE::Point_2<double> Point_2;
typedef AE::Less_2<double> Less_2;

template <class InputIterator, class OutputIterator, class Less>
OutputIterator sort(InputIterator first, InputIterator beyond, OutputIterator result, Less less)
{
  std::vector<typename std::iterator_traits<InputIterator>::value_type> random_arr;
  std::copy(first, beyond, std::back_inserter(random_arr));
  std::sort(random_arr.begin(), random_arr.end(), less);

  for (auto i = random_arr.begin(); i != random_arr.end(); ++i)
  {
    *(result++) = *i;
  }
  return result;
}

int main(int argc, char **argv)
{
  std::vector<Point_2> P;
  std::vector<Point_2> C;
  std::list<Point_2> S;

  std::ifstream F(argv[1]);
  int n;
  F >> n;
  double x, y;
  for (int i = 1; i <= n; ++i)
  {
    F >> x;
    F >> y;
    P.push_back(Point_2(x, y));
  }
  F.close();

  Point_2 A[n];
  A[n] = {};
  std::copy(P.begin(), P.end(), A);

  Less_2 xy_less;
  C = P;
  std::sort(C.begin(), C.end(), xy_less);
  // reserve space for the sorted
  std::copy(P.begin(), P.end(), std::back_inserter(S));

  sort(P.begin(), P.end(), S.begin(), xy_less);
  assert(!std::is_sorted(P.begin(), P.end(), xy_less));
  assert(std::is_sorted(S.begin(), S.end(), xy_less));
  assert(std::equal(C.begin(), C.end(), S.begin()));
  sort(A, A + n, S.begin(), xy_less);
  assert(!std::is_sorted(A, A + n, xy_less));
  assert(std::is_sorted(S.begin(), S.end(), xy_less));
  assert(std::equal(C.begin(), C.end(), S.begin()));

  std::sort(P.begin(), P.end(), xy_less);
  assert(std::is_sorted(P.begin(), P.end(), xy_less));
  assert(std::equal(C.begin(), C.end(), P.begin()));
  std::sort(A, A + n, xy_less);
  assert(std::is_sorted(A, A + n, xy_less));
  assert(std::equal(C.begin(), C.end(), A));

  printf("exit success\n");
  return EXIT_SUCCESS;
}
