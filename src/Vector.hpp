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

template <typename T>
class VectorN
{
public:
    VectorN(size_t size, float* data);
    virtual ~VectorN(void);

public:
    VectorN<T> add(const VectorN<T>& vec);

public:
    size_t  _size;
    T*      _data;
};

};

#endif /* Vector_hpp */
