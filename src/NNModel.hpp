//
//  NNModel.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#ifndef NNModel_hpp
#define NNModel_hpp

#include <vector>
#include "NNLayer.hpp"

class NNModel
{
    // Total layers = input + inner + output
    static const uint32_t INNER_LAYERS = 2;
    static const uint32_t LAYERS = INNER_LAYERS + 2;

public:
    NNModel(uint32_t num_layers_ = LAYERS);
    ~NNModel(void);
    
public:
    uint32_t train(std::vector<float*>& training_data, uint8_t* label);
    void infer(std::vector<float*>& inference_data, uint8_t* label);

private:
    NNLayer* layers;
    
};

#endif /* NNModel_hpp */
