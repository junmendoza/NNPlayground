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

MatrixMN::MatrixMN(size_t rows, size_t cols, double** data)
    : _rows(rows),
      _cols(cols),
      _data(data)
{
}

MatrixMN::~MatrixMN(void)
{
}

VectorN MatrixMN::mul(const VectorN& rhs)
{
    assert(rhs._size == _cols);
    VectorN vec(rhs._size);
    for (int m = 0; m < vec._size; ++m) {
        for (int n = 0; n < vec._size; ++n) {
            vec._data[m] = rhs._data[m] * _data[m][n];
        }
    }
    return vec;
}

VectorN MatrixMN::operator*(const VectorN& rhs)
{
    return mul(rhs);
}

}
