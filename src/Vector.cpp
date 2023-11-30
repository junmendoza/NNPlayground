//
//  Vector.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#include "Vector.hpp"

namespace Math
{

template <typename T>
VectorN<T>::VectorN(size_t size, float* data)
    : _size(size),
      _data(data)
{
}

template <typename T>
VectorN<T>::~VectorN(void)
{
}


template <typename T>
VectorN<T> VectorN<T>::add(const VectorN<T>& vec)
{
    VectorN<T> vec_new(vec._size, NULL);
    for (int n = 0; n < vec_new._size; ++n) {
        vec_new._data[n] = _data[n] + vec._data[n];
    }
    return vec_new;
}

}
