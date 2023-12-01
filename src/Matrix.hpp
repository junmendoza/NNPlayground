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

class MatrixMN
{
public:
    MatrixMN(void);
    MatrixMN(size_t rows, size_t cols, double** data);
    ~MatrixMN(void);

    VectorN mul(const VectorN& vec);

public:
    size_t   _rows;
    size_t   _cols;
    double** _data;
};

}

#endif /* Matrix_hpp */
