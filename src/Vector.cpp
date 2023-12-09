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

VectorN::VectorN(const VectorN& rhs)
    : _size(rhs._size),
      _data(new double[rhs._size])
{
    for (size_t n = 0; n < _size; ++n) {
        _data[n] = rhs._data[n];
    }
}

VectorN VectorN::operator=(const VectorN& rhs)
{
    return VectorN(rhs);
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

void VectorN::initialize(size_t size)
{
    assert(0 == _size);
    assert(NULL == _data);
    _size = size;
    _data = new double[_size];
}

void VectorN::initDefaultValue(size_t size, double val)
{
    initialize(size);
    for (size_t n = 0; n < _size; ++n) {
        _data[n] = val;
    }
}

void VectorN::initRandomUintValue(size_t size, size_t min, size_t max)
{
    initialize(size);
    for (size_t n = 0; n < _size; ++n) {
        _data[n] = Utils::randomizeUint(min, max);
    }
}

void VectorN::initRandomDoubleValue(size_t size)
{
    initialize(size);
    for (size_t n = 0; n < _size; ++n) {
        _data[n] = Utils::randomizeDouble01();
    }
}

void VectorN::add(const VectorN& rhs)
{
    assert(_size == rhs._size);
    for (size_t n = 0; n < _size; ++n) {
        _data[n] = _data[n] + rhs._data[n];
    }
}

void VectorN::sub(const VectorN& rhs)
{
    assert(_size == rhs._size);
    for (size_t n = 0; n < _size; ++n) {
        _data[n] = _data[n] - rhs._data[n];
    }
}

void VectorN::mul(const MatrixMN& mat)
{
    assert(_size == mat._rows);
    size_t r, c;
    for (r = 0; r < mat._rows; ++r) {
        double accumulate = 0.0f;
        for (c = 0; c < mat._cols; ++c) {
            accumulate = accumulate + (_data[c] * mat._data[r][c]);
        }
        _data[r] = accumulate;
    }
}

}
