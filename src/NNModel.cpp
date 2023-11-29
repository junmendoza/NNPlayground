//
//  NNModel.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#include "NNModel.hpp"

NNModel::NNModel(uint32_t num_layers_)
    : num_layers(num_layers_)
{
    layers = new NNLayer[num_layers];
}

NNModel::~NNModel(void)
{
    SAFE_DELETE_ARRAY(layers);
}

void NNModel::setInputLayerActivation(const float* training_data_, NNLayer& input_layer_)
{
    // Set layer activation list from training_data activation list
}

TrainingParams NNModel::getTrainingParams(NNLayer* layers_)
{
    TrainingParams params;
    return params;
}

float* NNModel::sigmoid(float* activation)
{
    return activation;
}

void NNModel::forward(const std::vector<float*>& training_data)
{
    // For every MNIST training data
    for (int i = 0; i < training_data.size(); ++i) {
        // Assign current training data activation list to the input layer
        setInputLayerActivation(training_data[i], layers[0]);
        for (int j = 0; j < num_layers; ++j) {
            //float* new_activation = layers[j].activation * layers[j].weight_matrix + layers[j].bias;
            float* new_activation = NULL;
            layers[j+1].activation = sigmoid(new_activation);
        }
    }
}

void NNModel::backpropagate(const TrainingParams& params)
{
    // Adjust weights and biases based on training parameters
}

uint32_t NNModel::train(const std::vector<float*>& training_data, const uint8_t* label)
{
    uint32_t iterations = 0;
    for (int iterations = 0; iterations < MAX_ITERATIONS; ++iterations) {
        forward(training_data);
        TrainingParams params = getTrainingParams(layers);
        if (params.done) {
            break;
        }
        backpropagate(params);
    }
    return iterations;
}

void NNModel::infer(const std::vector<float*>& inference_data, const uint8_t* label)
{
}

