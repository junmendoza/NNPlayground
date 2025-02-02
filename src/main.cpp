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
    size_t data_size = mnist_train_data.getSingleDataSize();
    std::vector<double*> training_data = mnist_train_data.getImageData();
    std::vector<uint8_t> label_data = mnist_train_data.getLabelData();
    size_t iterations = (*model)->train(data_size, training_data, label_data);
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
    size_t data_size = mnist_infer_data.getSingleDataSize();
    std::vector<double*> inference_data = mnist_infer_data.getImageData();
    std::vector<uint8_t> label_data = mnist_infer_data.getLabelData();
    (*model)->infer(data_size, inference_data, label_data);
    return true;
}

int main(int argc, const char * argv[])
{
//#define TEST_RANDOM
#ifdef TEST_RANDOM
    Utils::testRandomizeUint();
    Utils::testRandomizeDouble();
#else
    Utils::Trace::strace("NN Image classification \n");
    
    NNModel* model = new NNModel();
    if (!TrainModel(&model)) {
        return -1;
    }
    
    if (!TestModel(&model)) {
        return -1;
    }
    SAFE_DELETE(model);
#endif
    return 0;
}
