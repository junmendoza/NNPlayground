//
//  Matrix.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "Utils.hpp"
#include "Vector.hpp"

namespace Math
{

template <typename T>
class MatrixMN
{
public:
    MatrixMN(size_t rows, size_t cols, T** data);
    ~MatrixMN(void);

    VectorN<T> mul(const VectorN<T>& vec);

public:
    size_t  _rows;
    size_t  _cols;
    T** _data;
};

}

#endif /* Matrix_hpp */
