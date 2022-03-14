#ifndef SORTING_ALGORITHMS_INTROSORT_H
#define SORTING_ALGORITHMS_INTROSORT_H
#include "mergesort.h"
#include <math.h>

template <typename T>
class IntroSort: public MergeSort<T> 
{
private:
      void isort( T* data, int start, int end, unsigned max_depth )
      {
        if( max_depth <= 0 ) MergeSort<T>::sort( &data[start], end - start );
        else
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
	    if(start < j) isort( data, start, j, max_depth - 1 );
	    if(end > i) isort( data, i, end, max_depth - 1 );
      }
  }

public:
  virtual void sort( T* start, unsigned size )
  {
    unsigned max_depth = 2 * log2( size );
    isort( start, 0, size - 1, max_depth );
  };
};

#endif //SORTING_ALGORITHMS_INTROSORT_H
