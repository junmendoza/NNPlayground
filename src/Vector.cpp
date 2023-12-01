//
//  Vector.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#include "Vector.hpp"

namespace Math
{

VectorN::VectorN(void)
{
}

VectorN::VectorN(size_t size, double* data)
    : _size(size),
      _data(data)
{
}

VectorN::~VectorN(void)
{
}


VectorN VectorN::add(const VectorN& vec)
{
    VectorN vec_new(vec._size, NULL);
    for (int n = 0; n < vec_new._size; ++n) {
        vec_new._data[n] = _data[n] + vec._data[n];
    }
    return vec_new;
}

}
