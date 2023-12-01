//
//  NNModel.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#include "NNModel.hpp"

NNModel::NNModel(uint32_t num_layers)
    : _num_layers(num_layers)
{
    _layers = new NNLayer[_num_layers];
}

NNModel::~NNModel(void)
{
    SAFE_DELETE_ARRAY(_layers);
}

TrainingParams NNModel::getTrainingParams(NNLayer* layers)
{
    TrainingParams params;
    return params;
}

Math::VectorN NNModel::sigmoid(const Math::VectorN& activation)
{
    return activation;
}

void NNModel::forward(const std::vector<Math::VectorN*>& training_data)
{
    // For every MNIST training data
    for (size_t i = 0; i < training_data.size(); ++i) {
        // Assign current training data activation list to the input layer
        _layers[0]._activation = *training_data[i];

        // Calculate activation for all inner layers and output layer
        for (size_t j = 0; j < _num_layers; ++j)
        {
#ifdef DEBUGME
            for (int n = 0; n < 200; ++n) {
                if (_layers[j]._activation._data[n] > 0.0f) {
                    Utils::Trace::strace("Layer: %d, Activation: %f\n", j, _layers[j]._activation._data[n]);
                }
            }
#endif
            Math::VectorN weighted = _layers[j]._weights * _layers[j]._activation;
            Math::VectorN weighted_bias = weighted + _layers[j]._bias;
            _layers[j+1]._activation = sigmoid(weighted_bias);
        }
    }
}

void NNModel::backpropagate(const TrainingParams& params)
{
    // Adjust weights and biases based on training parameters
}

uint32_t NNModel::train(const std::vector<Math::VectorN*>& training_data, const uint8_t* label)
{
    uint32_t iterations = 0;
    for (iterations = 0; iterations < MAX_ITERATIONS; ++iterations) {
        forward(training_data);
        TrainingParams params = getTrainingParams(_layers);
        if (params.done) {
            break;
        }
        backpropagate(params);
    }
    return iterations;
}

void NNModel::infer(const std::vector<Math::VectorN*>& inference_data, const uint8_t* label)
{
}

