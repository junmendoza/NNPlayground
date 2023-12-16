//
//  NNModel.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#ifndef NNModel_hpp
#define NNModel_hpp

#include <vector>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "NNLayer.hpp"

class NNModel
{
enum LAYER_ID {
    INPUT,
    LAYER1,
    OUTPUT,
    COUNT
};

static const size_t MAX_ITERATIONS = 10;
static const size_t LAYER1_NEURONS = 16;
static const size_t OUTPUT_LAYER_NEURONS = 10;
static constexpr double COST_THRESHOLD = 0.2f;

public:
    NNModel(size_t num_layers = LAYER_ID::COUNT);
    ~NNModel(void);
    
public:
    void setupLayers(size_t input_layer_neurons);
    void sigmoid(Math::VectorN& activation);
    size_t train(const size_t& data_size, const std::vector<double*>& training_data, const std::vector<uint8_t>& label);
    double forward(const std::vector<double*>& training_data, const std::vector<uint8_t>& label);
    void backpropagate(const uint8_t label, const LAYER_ID idx, double delta = 0.0f);
    void adjustBias(const double delta, const LAYER_ID idx, size_t act_idx);
    void adjustWeights(const double delta, const LAYER_ID idx);
    double calculateCost(const NNLayer& output_layer, uint8_t label);
    void infer(const size_t& data_size, const std::vector<double*>& inference_data, const std::vector<uint8_t>& label);

private:
    size_t   _num_layers;
    NNLayer* _layers;
    
};

#endif /* NNModel_hpp */
