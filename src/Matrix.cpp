//
//  Matrix.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#include "Matrix.hpp"

namespace Math
{

template <typename T>
MatrixMN<T>::MatrixMN(size_t rows, size_t cols, T** data)
    : _rows(rows),
      _cols(cols),
      _data(data)
{
}

template <typename T>
MatrixMN<T>::~MatrixMN(void)
{
}


template <typename T>
VectorN<T> MatrixMN<T>::mul(const VectorN<T>& vec)
{
    VectorN<T> vec_new(vec._size, NULL);
    for (int n = 0; n < vec_new._size; ++n) {
    }
    return vec_new;
}

}
