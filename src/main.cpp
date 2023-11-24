//
//  main.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#include <vector>
#include "Utils.hpp"
#include "NNModel.hpp"
#include "MNISTData.hpp"

static const std::string mnist_path = "/Users/junmendoza/NNPlayground/mnist/";

bool TrainModel(NNModel** model)
{
    // Load training data
    std::string mnist_train_image = mnist_path + "train-images.idx3-ubyte";
    std::string mnist_train_label = mnist_path + "train-labels.idx1-ubyte";
    MNISTData mnist_train_data(mnist_train_image, mnist_train_label);
    if (!mnist_train_data.loadData()) {
        return false;
    }
    std::vector<float> training_data = mnist_train_data.getActivation();
    std::vector<uint8_t> label_data = mnist_train_data.getLabel();
    uint32_t iterations = (*model)->train(training_data, label_data);
    Utils::Trace::strace("Image training took %d iterations.\n", iterations);
    return true;
}

bool TestModel(NNModel** model)
{
    // Load inference data
    std::string mnist_infer_image = mnist_path + "t10k-images.idx3-ubyte";
    std::string mnist_infer_label = mnist_path + "t10k-labels.idx1-ubyte";
    MNISTData mnist_infer_data(mnist_infer_image, mnist_infer_label);
    if (!mnist_infer_data.loadData()) {
        return false;
    }
    
    // Test NN using inference data
    std::vector<float> inference_data = mnist_infer_data.getActivation();
    std::vector<uint8_t> label_data = mnist_infer_data.getLabel();
    (*model)->infer(inference_data, label_data);
    return true;
}

#include <iostream>

int main(int argc, const char * argv[])
{        
    Utils::Trace::strace("NN Image classification \n");
    
    NNModel* model = new NNModel();
    if (!TrainModel(&model)) {
        return -1;
    }
    
    if (!TestModel(&model)) {
        return -1;
    }
    SAFE_DELETE(model);
    
    return 0;
}
