//
//  Matrix.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#include "Matrix.hpp"

namespace Math
{

MatrixMN::MatrixMN(void)
{
}

MatrixMN::MatrixMN(size_t rows, size_t cols)
    : _rows(rows),
      _cols(cols)
{
    setup(_rows, _cols);
}

MatrixMN::~MatrixMN(void)
{
    for (size_t r = 0; r < _rows; ++r) {
        SAFE_DELETE_ARRAY(_data[r]);
    }
    SAFE_DELETE_ARRAY(_data);
}

void MatrixMN::setup(size_t rows, size_t cols)
{
    _data = new double*[rows];
    for (size_t r = 0; r < rows; ++r) {
        _data[r] = new double[cols];
    }
}

VectorN MatrixMN::mul(const VectorN& rhs)
{
    assert(rhs._size == _cols);
    VectorN vec(rhs._size);
    for (size_t r = 0; r < vec._size; ++r) {
        for (size_t c = 0; c < vec._size; ++c) {
            vec._data[r] = rhs._data[r] * _data[r][c];
        }
    }
    return vec;
}

VectorN MatrixMN::operator*(const VectorN& rhs)
{
    return mul(rhs);
}

}
