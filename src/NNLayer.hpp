//
//  NNLayer.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 28/11/2023.
//

#ifndef NNLayer_hpp
#define NNLayer_hpp

#include "Utils.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

struct NNLayer
{
    NNLayer(void){}
    ~NNLayer(void){}
    size_t         _label;          // Image identifier
    size_t         _neurons;        // Neuron count
    Math::VectorN  _activation;     // Activation vector
    Math::VectorN  _bias;           // Bias vector

    // Weight matrix [rows X cols]
    // The rows are the number of neurons in the next resulting layer
    // The cols are the number of neurons in the current layer
    // The weight matrix is multipled with the activation list in the current layer
    // The output is the activation list in the next layer
    Math::MatrixMN _weights;
};

#endif /* NNLayer_hpp */
