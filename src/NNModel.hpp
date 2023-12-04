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

struct TrainingParams {
    bool done;
};

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

public:
    NNModel(size_t num_layers = LAYER_ID::COUNT);
    ~NNModel(void);
    
public:
    void setupLayers(size_t input_layer_neurons);

    void sigmoid(Math::VectorN& activation);
    void forward(const std::vector<Math::VectorN*>& training_data);
    size_t train(const std::vector<Math::VectorN*>& training_data, const uint8_t* label);
    void infer(const std::vector<Math::VectorN*>& inference_data, const uint8_t* label);

    double calculateCost(const NNLayer* layers);
    TrainingParams getTrainingParams(const NNLayer* layers);
    void backpropagate(const TrainingParams& params);

private:
    size_t   _num_layers;
    NNLayer* _layers;
    
};

#endif /* NNModel_hpp */
