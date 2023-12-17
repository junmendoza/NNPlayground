# README NNPlayground

# Tasklist 
## 14-Nov-23
- [x] Function: MNIST::loadDatabase(...)
- [x] Function: MNIST::loadImageFile(...)
- [x] Function: MNIST::loadLabelFile(...)
- [x] Document: Outline MNIST file format
- [x] Document: Outline MNIST single image format
- [x] Document: Outline MNIST data structure

## 15-Nov-23
- [x] Download mnist training set and example binaries


## 20-Nov-23
- [x] Whats the train function params?
- [x] How are the 60k image and labels fed into the train function?
- [x] What does 1 train iteration need?

## 22-Nov-23
- [x] Setup function: Input layer. Initialize and normalize
- [x] Setup function: Normalize pixel data and assign to input layer

## 23-Nov-23
- [x] forward function
- [x] backpropagate function
- [x] Train function: forward and backpropagate


## 24-Nov-23
- [x] Where is the label used? Which function? Layer is passed to the train function, along with the pixel image

## 25-Nov-23
- [x] Matrix class: Arbitrary size MxN matrix
- [x] Matrix class: Multiply matrix x vector


## 30-Nov-23
- [x] Vector class: Arbitrary size vector


## 01-Dec-23
- [x] Init layer function

## 01-Dec-23
- [x] VectorN copy constructor and operator=
- [x] MatrixMN copy constructor and operator=
- [x] Test VectorN in forward function if it still SIGABORTs on assignment

## 04-Dec-23
- [x] Calculate sigmoid
- [x] How is cost function calculated?
- [x] How is cost function used in learning?
- [x] What can be tweaked in a layer?
- [x] How is a layer tweaked?

## 09-Dec-23
- [x] Randomize: Impl randomizer function
- [x] Randomize: Bias
- [x] Randomize: Weights


## 10-Dec-23
- [x] What is the structure of the negative gradient?
- [x] How are each element of the negative gradient calculated?

## 13-Dec-23
- [x] Design the calculateGradient recursive function


# Git Usage (This project)
## Set the PAT from the command line
```
git remote set-url origin https://junmendoza:<TOKEN>@github.com/junmendoza/NNPlayground.git
```
## Push commit to github
```
git push -u origin main
```


# Image classifier NN overview
- The number of neuron are the number of image pixels i.e. If input image is 28x28 pixels, then input layer has 28x28=784 neurons
- A neuron holds a number betwen 0 and 1 known as the activation
- Pixel data must be normalized to a value between 0 and 1 and set as the activation of each neuron in the input layer

## Weight Matrix
- A weight matrix represents the weights connected from 2 layers.
- The dimensions are [rows X cols]
- The rows are the number of neurons in the next resulting layer
- The cols are the number of neurons in the current layer
- The weight matrix is multipled with the activation list in the current layer
- The output is the activations of each neuron in the next layer


## Learning phase
- Learning means taking the output of the cost function and calculating the new weights and biases for each layer
- The weights and biases are adjusted for each iteration with the goal of the cost function returning a smaller value
- Determining the weights and biases that minimizes the average cost is also known as calculating the gradient descent of a function, where the function is the entire NN
- Each layer will have a function whose parameter is the negative gradient (ngrad). This parameter is used to adjust the layer weights and bias.
```
void backpropagate(idx, label, delta = 0.0f)
{
    if (INPUT == idx) return;

    // For each activation in the current layer
    for (act_idx = 0 to layers[idx].act) {
        // Calculate the nudge delta of this neuron
        nudge_up = OUTPUT == idx ? act_idx == label : delta > 0.0f;
        delta = (1 & (int)nudge_up) - layers[idx].act[act_idx];

        // Adjust weights and bias and backpropagate only if the neuron needs adjustment
        if (0.0f != delta) {
            adjustBias(layer[idx], act_idx, delta);
            adjustWeights(layer[idx], act_idx, delta);
            backpropagate(layer[idx-1], label, delta);
        }
    }
}

void adjustBias(layer, act_idx, delta)
{
    // Calculate the new bias given the delta
    bias = calculateNewBias(layer, act_idx, delta);
    applyBias(layer, act_idx, delta);
}

void adjustWeights(layer, act_idx, delta)
{
    // Calculate the negative gradient of the weights of this layer given:
    // * The delta
    // * The activations of the previous layer
    gradient = calculateGradient(layer, act_idx, delta);
    applyGradient(layer, act_idx, gradient);
}
```

### Cost function
- The cost function takes the entire network and outputs 1 cost value
- The input are all the training data for each iteration
- The cost per input is calculated as:

```
    // If input is 2, then
    cost =
        (output_layer.activation[0] - 0)^2 +
        (output_layer.activation[1] - 0)^2 +
        (output_layer.activation[2] - 1)^2 +
        (output_layer.activation[3] - 0)^2 +
        (output_layer.activation[4] - 0)^2 +
        (output_layer.activation[5] - 0)^2 +
        (output_layer.activation[6] - 0)^2 +
        (output_layer.activation[7] - 0)^2 +
        (output_layer.activation[8] - 0)^2 +
        (output_layer.activation[9] - 0)^2
```
- The average cost of the entire network is the average cost of all training input
- The average cost is calculated per iteration. For each iteration if the average cost is low enough, then the training is completed

```
double calculateCost(output_layer, label)
{
    double cost = 0.0;
    for (i = 0 to output_layer.size) {
        double c = output_layer.activation[i] - (label & i)
        cost += c * c;
    }
    return cost;
}
```


# MNIST
http://yann.lecun.com/exdb/mnist/

## MNIST image format
### MNIST are a set of binray files containing image data that can be used to test and run neural network training and inference
- train-images-idx3-ubyte: training set images
- train-labels-idx1-ubyte: training set labels
- t10k-images-idx3-ubyte:  test set images
- t10k-labels-idx1-ubyte:  test set labels

## Image file 
### Header
### List of 28x28 images.Pixels are organized row-wise. 
    Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).

## Label file
### Header
### Labels that specify the associated images in the image file. 
    The labels values are 0 to 9. 

## MNIST data structure
```
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
    double*    activation;    // activation vector
    double**   weight_matrix; // weight matrix [layer.neurons X prev_layer.neurons]
    uint8_t*  bias;           // bias vector
}

// Image file
ImageHeader image_header = parseImageHeader(train-images-idx3-ubyte)
vector<double*> image_list = parseImageData(train-images-idx3-ubyte)

// Label file
LabelHeader label_header = parseLabelHeader(train-labels-idx1-ubyte)
vector<int> label_list = parseLabelData(train-labels-idx1-ubyte)

void Model::initLayers(void)
{
    // Init weights, biases, activation to its default values
}

void Model::setInputLayerActivation(const double* training_data, Layer& input_layer)
{
    // Set layer activation list from training_data activation list
}

void Model::forward(const vector<const double*>& train_data, vector<Layer>& layers)
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

uint32_t Model::train(const vector<const double*>& training_data, const uint32_t* labels)
{
    initLayers();
    for (int i = 0 to MAX_ITERATIONS) {
        ave_cost = forward(training_data, labels);
        if (ave_cost <= threshold) break;

        // Backpropagate for each training data
        for (int j = 0 to train_data.cnt) {
            backpropagate(OUTPUT, labels[j]);
        }
    }
    return i;
} 
```

