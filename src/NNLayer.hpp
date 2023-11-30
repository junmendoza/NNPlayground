//
//  NNLayer.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 28/11/2023.
//

#ifndef NNLayer_hpp
#define NNLayer_hpp

#include "Utils.hpp"

class NNLayer
{
public:
    NNLayer(void);
    ~NNLayer(void);

public:
    uint32_t  _label;           // Image identifier

    uint32_t  _neurons;         // Neuron count
    float*    _activation;      // Activation vector
    uint8_t*  _bias;            // Bias vector

    uint32_t  _mat_row;         // Weight matric row count
    uint32_t  _mat_col;         // Weight matric column count
    float**   _mat_weights;     // Weight matrix [layer.neurons X prev_layer.neurons]
};


#endif /* NNLayer_hpp */
