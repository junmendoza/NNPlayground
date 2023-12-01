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

void NNModel::setInputLayerActivation(const double* training_data, NNLayer& input_layer)
{
    // Set layer activation list from training_data activation list
}

TrainingParams NNModel::getTrainingParams(NNLayer* layers)
{
    TrainingParams params;
    return params;
}

double* NNModel::sigmoid(double* activation)
{
    return activation;
}

void NNModel::forward(const std::vector<double*>& training_data)
{
    // For every MNIST training data
    for (int i = 0; i < training_data.size(); ++i) {
        // Assign current training data activation list to the input layer
        setInputLayerActivation(training_data[i], _layers[0]);
        for (int j = 0; j < _num_layers; ++j) {
            Math::VectorN new_activation; //_layers[j]._weights.mul(_layers[j]._activation);//.add(_layers[j]._bias);
            //double* new_activation = NULL;
            //_layers[j+1]._activation._data = sigmoid(new_activation);
        }
    }
}

void NNModel::backpropagate(const TrainingParams& params)
{
    // Adjust weights and biases based on training parameters
}

uint32_t NNModel::train(const std::vector<double*>& training_data, const uint8_t* label)
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

void NNModel::infer(const std::vector<double*>& inference_data, const uint8_t* label)
{
}

