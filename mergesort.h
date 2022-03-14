#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include "mock.h"


template <typename T>
class MergeSort: public sort_alg<T>
{
private:
  void merge( T* src, T* dest, unsigned part_size, unsigned index, unsigned max)
  {
    unsigned j = 0, k = part_size; //iteratory podtablic wej sciowych

    for( unsigned i = 0; i+index < max && i < 2*part_size; ) //iterator tablicy wyjsciowej
      {

	if( j < part_size && j+index < max) 
	  {
	    if( k < 2*part_size && k+index < max ) dest[index + i++] = ( src[ index + j ] > src[ index + k ] ? src[ index + k++ ] : src[index + j++] );	//oba wejscia dostepne
	    else dest[index + i++] = src[index + j++]; //tylko j dostepne
	  }
	else if( k < 2*part_size && k+index < max ) dest[index + i++] = src[index + k++]; //tylko k dostepne
      }
  };

  void move_result( T* src, T* dest, unsigned size)
  {
    for(unsigned i = 0; i < size; ++i) dest[i] = src[i];
  };

public:
  virtual void sort( T* start, unsigned size )
  {
    unsigned index = 0; //
    bool result_in_aux = true;

    T* aux = new T[size];

    for( unsigned part_size = 1; part_size < size; part_size *= 2 ) //po rozmiarze
      {
	for( index = 0; index < size; index += 2*part_size) //po podtablicach
	  {
	    if( result_in_aux ) merge( start, aux, part_size, index, size );
	    else merge( aux, start, part_size, index, size );
	  }
	result_in_aux = !result_in_aux;
      }

    if( !result_in_aux ) move_result( aux, start, size);
    delete aux;
  };
};
#endif //SORTING_ALGORITHMS_MERGESORT_H
