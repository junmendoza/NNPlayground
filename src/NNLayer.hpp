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

private:
    uint32_t  label;         // image identifier
    float*    activation;    // activation vector
    float**   weight_matrix; // weight matrix [layer.neurons X prev_layer.neurons]
    uint8_t*  bias;          // bias vector
};


#endif /* NNLayer_hpp */
