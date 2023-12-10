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
    // r = layer1.neurons
    // c = layer0.neurons
    _layers[INPUT ]._weights.setup(LAYER1_NEURONS, input_layer_neurons);
    _layers[INPUT ]._weights.setDefaultValue(0.1);
    _layers[INPUT ]._bias.initRandomUintValue(input_layer_neurons, 1, 5);
    _layers[INPUT ]._activation.initRandomDoubleValue(input_layer_neurons);

    // r = layer2.neurons
    // c = layer1.neurons
    _layers[LAYER1]._weights.setup(OUTPUT_LAYER_NEURONS, LAYER1_NEURONS);
    _layers[LAYER1]._weights.setDefaultValue(0.3);
    _layers[LAYER1]._bias.initRandomUintValue(LAYER1_NEURONS, 1, 5);
    _layers[LAYER1]._activation.initRandomDoubleValue(LAYER1_NEURONS);

    // Output layer has no weight matrix
    _layers[OUTPUT]._bias.initRandomUintValue(OUTPUT_LAYER_NEURONS, 1, 5);
    _layers[OUTPUT]._activation.initRandomDoubleValue(OUTPUT_LAYER_NEURONS);
}

void NNModel::sigmoid(Math::VectorN& activation)
{
    for (size_t n = 0; n < activation._size; ++n) {
        activation._data[n] = 1 / (1 + exp(-activation._data[n]));
    }
}

size_t NNModel::train(const size_t& data_size,
                      const std::vector<double*>& training_data,
                      const std::vector<uint8_t>& label)
{
    size_t input_layer_neurons = data_size;
    setupLayers(input_layer_neurons);

    uint32_t iterations = 0;
    for (iterations = 0; iterations < MAX_ITERATIONS; ++iterations) {
        double ave_cost = forward(training_data, label);
        Utils::Trace::strace("Training iteration: %d, cost: %f.\n", iterations, ave_cost);
        bool done = backpropagate(ave_cost);
        if (done) {
            break;
        }
    }
    return iterations;
}

double NNModel::forward(const std::vector<double*>& training_data, const std::vector<uint8_t>& label)
{
    // For every MNIST training data, calculate the activation for all layers
    double ave_cost = 0.0f;
    for (size_t i = 0; i < training_data.size(); ++i)
    {
        // Assign current training data activation list to the input layer
        _layers[0]._activation._data = training_data[i];
//#define DEBUG_INPUTLAYER_ACTIVATION
#ifdef DEBUG_INPUTLAYER_ACTIVATION
        for (int n = 0; n < 10; ++n) {
            if (_layers[INPUT]._activation._data[n] > 0.0f) {
                Utils::Trace::strace("Layer: %d, Activation: %f\n", INPUT, _layers[INPUT]._activation._data[n]);
            }
        }
#endif

        // Calculate activation for all inner layers and output layer
        for (size_t j = 1; j < _num_layers; ++j)
        {
//#define DEBUG_INNERLAYER_ACTIVATION
#ifdef DEBUG_INNERLAYER_ACTIVATION
            for (int n = 0; n < 10; ++n) {
                if (_layers[j]._activation._data[n] > 0.0f) {
                    Utils::Trace::strace("Layer: %d, Activation: %f\n", j, _layers[j]._activation._data[n]);
                }
            }
#endif
            // Calculating the layer activation
            // * Applying matrix and vector arithmetic on the layer activation vector
            // * Do not create multiple temp copies of the activation vector
            _layers[j]._activation.mul(_layers[j-1]._weights);
            _layers[j]._activation.sub(_layers[j]._bias);
            sigmoid(_layers[j]._activation);
        }
        ave_cost += calculateCost(_layers[OUTPUT], label[i]);
    }
    return ave_cost / training_data.size();
}

bool NNModel::backpropagate(const double& ave_cost)
{
    const double COST_THRESHOLD = 0.0f;
    if (ave_cost <= COST_THRESHOLD) {
        return true;
    }

    // Determine how to lower the average cost in the layer

    // Adjust weights and biases based on training parameters

    // This backprop cycle is not yet done
    return false;
}

double NNModel::calculateCost(const NNLayer& output_layer, uint8_t label)
{
    double cost = 0.0;
    for (size_t n = 0; n < output_layer._activation._size; ++n) {
        double c =  output_layer._activation._data[n] - (double)(label == n);
        double c2 = c * c;
        cost += c2;
    }
    return cost;
}

void NNModel::infer(const size_t& data_size,
                    const std::vector<double*>& inference_data,
                    const std::vector<uint8_t>& label)
{
}
