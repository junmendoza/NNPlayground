//
//  NNModel.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#include "NNModel.hpp"

NNModel::NNModel(uint32_t num_layers_)
{
    layers = new NNLayer[num_layers_];
}

NNModel::~NNModel(void)
{
    SAFE_DELETE_ARRAY(layers);
}

uint32_t NNModel::train(std::vector<float>& training_data, std::vector<uint8_t> label)
{
    return 0;
}

void NNModel::infer(std::vector<float>& inference_data, std::vector<uint8_t> label)
{
}

