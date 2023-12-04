//
//  Vector.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#ifndef Vector_hpp
#define Vector_hpp

#include "Utils.hpp"
#include "Matrix.hpp"

namespace Math
{
class MatrixMN;
class VectorN
{
public:
    VectorN(void);
    VectorN(const VectorN& rhs);
    VectorN operator=(const VectorN& rhs);
    VectorN(size_t size);
    ~VectorN(void);

public:
    void setDefaultValue(double val);
    void initialize(size_t size, double val);
    void add(const VectorN& rhs);
    void mul(const MatrixMN& mat);

public:
    size_t  _size;
    double* _data;
};

};

#endif /* Vector_hpp */
