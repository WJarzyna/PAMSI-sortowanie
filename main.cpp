#include <iostream>
#include <unistd.h>
#include "mergesort.h"
#include "quicksort.h"
#include "introsort.h"

using std::cout;
using std::string;
using std::swap;

//#define TEST_CHECK
//#define TEST_VERBOSE
//#define TEST_QTY


#ifdef TEST_QTY
#define TAB_SIZES {10, 50, 10, 50, 10}
#define N_RUNS 1
#else
#define TAB_SIZES {10000, 50000, 100000, 500000, 1000000}
#define N_RUNS 100
#endif

void run( sort_alg<int>& base_obj, void (sort_alg<int>::*alg)( int*, unsigned ), int sort_pm, unsigned tab_size ) 
{
  struct timespec begin, end;
  double run_t = 0;
  int* data = NULL;
  unsigned size_to_presort = 0;
  
  MergeSort<int> presort;
	      
  for( unsigned i = 0; i < N_RUNS; ++i )
    {
      data = new int[ tab_size ];
      for( unsigned i = 0; i < tab_size; ++i ) data[i] = rand() % 1000;
     
      if( sort_pm != 0 )
	{
	  size_to_presort = (abs( sort_pm ) * tab_size) / 1000;
	  presort.sort( data, size_to_presort );
	}
       
      if( sort_pm < 0 )
	{
	  for( unsigned i = 0; i < size_to_presort/2; ++i ) swap( data[i], data[size_to_presort -1 -i] );
	}

#ifdef TEST_VERBOSE
      cout<<'\n';
      for( unsigned i = 0; i < tab_size; ++i ) cout<<data[i]<<' ';
      cout<<'\n';
#endif
      
      clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
      (base_obj.*alg)(data, tab_size);
      clock_gettime(CLOCK_MONOTONIC_RAW, &end);
      run_t += (end.tv_sec  - begin.tv_sec)*1000 + (end.tv_nsec  - begin.tv_nsec)/1e6;

#ifdef TEST_VERBOSE
      cout<<'\n';
      for( unsigned i = 0; i < tab_size; ++i ) cout<<data[i]<<' ';
      cout<<'\n';
#endif
      
#ifdef TEST_CHECK
      for( unsigned i = 0; i < tab_size - 1; ++i )
	{
	  if( data[ i+1 ] < data[i] ) cout<<"\n\nSORTING FAILED\n\n";
	  return;
	}
#endif
      
      delete data;
    }    
  cout << '\t' << run_t << " ms\n";
}


int main( void )
{
  srand(time(NULL));
  
  string alg_v[3] = {"Merge sort","Quick sort","Intro sort"};
  unsigned size_tab[5] = TAB_SIZES;
  string tests_v[8] = {"fully random:     ","first 25% sorted: ","first 50% sorted: ","first 75% sorted: ","first 95% sorted: ","first 99% sorted: ","first 99.7% sorted: ","fully reverse sorted: "};
  int test_n[8] = {0, 250, 500, 750, 950, 990, 997, -1000};

  MergeSort<int> merger;
  QuickSort<int> quicke;
  IntroSort<int> intro;

  sort_alg<int>* alg_tab[3] = { &merger, &quicke, &intro };

  cout << "Testing sorting algorithms effectiveness on 100-element batches of variable sized integer arrays, with various levels of pre-sorting, based on execution time\n\n";

  for( unsigned alg = 0; alg < 3; ++alg )
    {
      cout << "Sorting algorithm: " << alg_v[ alg ] << '\n';

      for( unsigned size = 0; size < 5; ++size)
	{
	  cout << "Table size: " << size_tab[ size ] << '\n';
	  
	  for( unsigned test = 0; test < 8; ++test )
	    {
	      cout << "Pre-sorting variant:\t" << tests_v[ test ];

	      run( *(alg_tab[alg]), &sort_alg<int>::sort, test_n[test], size_tab[size] );
	    }
	  cout << '\n';
	}
      cout << "##################################################################################################################################\n\n\n";
    }
  cout<< "Testing done, thank you.\n";
}
