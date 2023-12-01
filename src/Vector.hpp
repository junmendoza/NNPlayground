//
//  Vector.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#ifndef Vector_hpp
#define Vector_hpp

#include "Utils.hpp"

namespace Math
{
class VectorN
{
public:
    VectorN(void);
    VectorN(size_t size);
    ~VectorN(void);

public:
    VectorN add(const VectorN& rhs);
    VectorN operator+(const VectorN& rhs);

public:
    size_t  _size;
    double* _data;
};

};

#endif /* Vector_hpp */
