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
static constexpr double DEFAULT_VAL = 0.0;

public:
    MatrixMN(void);
    MatrixMN(size_t rows, size_t cols);
    ~MatrixMN(void);

    void setup(size_t rows, size_t cols);
    void setDefaultValue(void);
    void setDefaultTestValuesByRow(void);
    void setDefaultTestValuesByCol(void);
    void print(size_t rows, size_t cols);
    VectorN mul(const VectorN& rhs);
    VectorN operator*(const VectorN& rhs);

public:
    size_t   _rows;
    size_t   _cols;
    double** _data;
};

}

#endif /* Matrix_hpp */
