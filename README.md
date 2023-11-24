# README NNPlayground

# Tasklist 
## As of 14-Nov-23
[x] Function: MNIST::loadDatabase(...)
[x] Function: MNIST::loadImageFile(...)
[x] Function: MNIST::loadLabelFile(...)
[x] Document: Outline MNIST file format
[x] Document: Outline MNIST single image format
[x] Document: Outline MNIST data structure

## As of 15-Nov-23
[x] Download mnist training set and example binaries


## As of 20-Nov-23
[x] Whats the train function params?
[x] How are the 60k image and labels fed into the train function?
[x] What does 1 train iteration need?

## As of 22-Nov-23
[ ] Setup function: Input layer. Initialize and normalize
[ ] Setup function: Normalize pixel data and assign to input layer
[ ] Setup function: inner layers - vector of vector<float>
[ ] Setup function: Initialize weight matrix and bias for all layers

## As of 23-Nov-23
[ ] forward function
[ ] backpropagate function
[ ] Train function: forward and backpropagate


## As of 24-Nov-23
[ ] Where is the label used? Which function? Layer is passed to the train function, along with the pixel image

# Image classifier NN overview
## Input layer: The number of neuron are the number of image pixels i.e. If input image is 28x28 pixels, then input layer has 28x28=784 neurons
## A neuron holds a number betwen 0 and 1 known as the activation
## Pixel data must be normalized to a value between 0 and 1 and set as the activation of each neuron in the input layer
## 
  

# MNIST
http://yann.lecun.com/exdb/mnist/

## MNIST image format
### MNIST are a set of binray files containing image data that can be used to test and run neural network training and inference
#### train-images-idx3-ubyte: training set images 
#### train-labels-idx1-ubyte: training set labels 
#### t10k-images-idx3-ubyte:  test set images 
#### t10k-labels-idx1-ubyte:  test set labels

## Image file 
### Header
### List of 28x28 images.Pixels are organized row-wise. 
    Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).

## Label file 
### Header
### Labels that specify the associated images in the image file. 
    The labels values are 0 to 9. 

## MNIST data structure

ImageHeader
    int magic_number; // Compare with training/inference header constant 
    int items;        // Compare with label count
    int rows;         // Num rows per image
    int colums;       // Num cols per image 
    
LabelHeader
    int magic_number; // Compare with training/inference header constant 
    int items;        // Compare with image count
    
    
class Layer
{
    uint32_t  label;         // image identifier
    float*    activation;    // activation vector
    float**   weight_matrix; // weight matrix [layer.neurons X prev_layer.neurons]
    uint8_t*  bias;          // bias vector 
}

// Image file
ImageHeader image_header = parseImageHeader(train-images-idx3-ubyte)
vector<NNData> image_list = parseImageData(train-images-idx3-ubyte)

// Label file
LabelHeader label_header = parseLabelHeader(train-labels-idx1-ubyte)
vector<int> label_list = parseLabelData(train-labels-idx1-ubyte)

void Model::initLayers(vector<Layer>& layers) 
{
    // Init weights, biases, activation to its default values
}

void Model::setInputLayerActivation(const vector<float>& training_data, Layer& input_layer)
{
    // Set layer activation list from training_data activation list
}

void Model::forward(const vector<NNData>& train_data, vector<Layer>& layers) 
{
    // For every MNIST training data
    for (int i = 0 to train_data.cnt) {
        // Assign current training data activation list to the input layer 
        setInputLayerActivation(train_data[i].activation, layer[0]);
        for (int j = 0 to layer.cnt-1) {
            layer[j+1].activation = sigmoid(layer.activation[j] * layer.weight_matrix[j] + layer.bias[j]);
        }
    }
}

void Model::backpropagate(const TrainingParams& params, vector<Layer>& layers)
{
    // Adjust weights and biases based on training parameters
}

uint32_t Model::train(
    const vector<vector<float>>& training_data, 
    const vector<uint32_t> label)
{
    initLayers(layers);
    for (!int n = 0; n < MAX_ITERATIONS; ++n) {
        forward(training_data, layers);
        TrainingParams params = getTrainingParams(layers);
        if (params.done) {
            break;
        }
        backpropagate(params, layers);
    }
    return n;
} 

    

