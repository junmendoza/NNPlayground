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


VectorN MatrixMN::mul(const VectorN& vec)
{
    VectorN vec_new(vec._size, NULL);
    for (int n = 0; n < vec_new._size; ++n) {
    }
    return vec_new;
}

}
