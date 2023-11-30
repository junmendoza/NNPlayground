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


struct TrainingParams {
    bool done;
};

class NNModel
{
static const uint32_t MAX_ITERATIONS = 10;

// Total layers = input + inner + output
static const uint32_t INNER_LAYERS = 2;
static const uint32_t LAYERS = INNER_LAYERS + 2;

public:
    NNModel(uint32_t num_layers = LAYERS);
    ~NNModel(void);
    
public:
    void setInputLayerActivation(const float* training_data_, NNLayer& input_layer);
    TrainingParams getTrainingParams(NNLayer* layers);
    float* sigmoid(float* activation);
    void backpropagate(const TrainingParams& params);
    void forward(const std::vector<float*>& training_data);
    uint32_t train(const std::vector<float*>& training_data, const uint8_t* label);
    void infer(const std::vector<float*>& inference_data, const uint8_t* label);

private:
    uint32_t _num_layers;
    NNLayer* _layers;
    
};

#endif /* NNModel_hpp */
