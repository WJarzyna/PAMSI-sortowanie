#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H
#include "mock.h"

using std::swap;

template <typename T>
class QuickSort: public sort_alg<T>
{
private:
  void qsort(T* data, int start, int end)
  {
    T pivot = data[ (start + end) / 2 ];
    int i = start, j = end;

    while(i <= j)
      {
        while( data[i] < pivot ) ++i;
        while( data[j] > pivot ) --j;
	
        if(i <= j)
	  {
            swap( data[i], data[j] );
            ++i;
            --j;
	  }
      }
    if(start < j) qsort( data, start, j );
    if(end > i) qsort( data, i, end );
  }

  
public:
  virtual void sort( T* data, unsigned size )
  {
    qsort( data, 0, size - 1);
  };

};
#endif //SORTING_ALGORITHMS_QUICKSORT_H

