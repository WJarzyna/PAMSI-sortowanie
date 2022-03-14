#pragma once
#include <iostream>

using std::cout;

template <typename T>
class sort_alg
{
public:
  virtual void sort( T* start, unsigned size )
  {
    cout<<"mock sorting algorithm"<<'\n';
  };
};
