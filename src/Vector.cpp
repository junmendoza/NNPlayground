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

VectorN::VectorN(size_t size)
    : _size(size)
{
    _data = new double[_size];
}

VectorN::~VectorN(void)
{
    SAFE_DELETE_ARRAY(_data);
}


VectorN VectorN::add(const VectorN& rhs)
{
    VectorN vec_new(rhs._size);
    for (int n = 0; n < vec_new._size; ++n) {
        vec_new._data[n] = _data[n] + rhs._data[n];
    }
    return vec_new;
}
VectorN VectorN::operator+(const VectorN& rhs)
{
    return add(rhs);
}

}
