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
    size_t         _label;          // Image identifier
    size_t         _neurons;        // Neuron count
    Math::VectorN  _activation;     // Activation vector
    Math::VectorN  _bias;           // Bias vector
    Math::MatrixMN _weights;        // Weight matrix [layer.neurons X prev_layer.neurons]
/*
    uint32_t  _label;       // Image identifier

    uint32_t  _neurons;     // Neuron count
    double*    _activation;  // Activation vector
    uint8_t*  _bias;        // Bias vector

    uint32_t  _mat_row;     // Weight matric row count
    uint32_t  _mat_col;     // Weight matric column count
    double**   _mat_weights; // Weight matrix [layer.neurons X prev_layer.neurons]
 */
};


#endif /* NNLayer_hpp */
