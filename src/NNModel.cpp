//
//  NNModel.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#include "NNModel.hpp"

NNModel::NNModel(size_t num_layers)
    : _num_layers(num_layers)
{
    _layers = new NNLayer[_num_layers];
}

NNModel::~NNModel(void)
{
    SAFE_DELETE_ARRAY(_layers);
}

void NNModel::setupLayers(size_t input_layer_neurons)
{
    // r = layer0.neurons
    // c = layer1.neurons
    _layers[INPUT ]._weights.setup(input_layer_neurons, LAYER1_NEURONS);

    // r = layer1.neurons
    // c = layer2.neurons
    _layers[LAYER1]._weights.setup(LAYER1_NEURONS, OUTPUT_LAYER_NEURONS);

    // Last layer has no weight matrix
    _layers[OUTPUT]._weights.setup(0, 0);
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

size_t NNModel::train(const std::vector<Math::VectorN*>& training_data, const uint8_t* label)
{
    size_t input_layer_neurons = training_data[0]->_size;
    setupLayers(input_layer_neurons);

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

double NNModel::calculateCost(const NNLayer* layers)
{
    return 0.0f;
}

TrainingParams NNModel::getTrainingParams(const NNLayer* layers)
{
    double cost = calculateCost(layers);
    UNUSED(cost);

    TrainingParams params;
    return params;
}

void NNModel::backpropagate(const TrainingParams& params)
{
    // Adjust weights and biases based on training parameters
}
