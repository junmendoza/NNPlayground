
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Image
{
public:
	Image(const std::string& img_file)
	{
	}
	~Image(){}
};

class NeuralNetwork
{
public:
	NeuralNetwork(){}
	~NeuralNetwork(){}

public:
	bool train(const Image& img)
	{
		return true;
	}

	uint32_t process(const Image& img)
	{
		return output;
	}

private:
	uint32_t output;
};

NeuralNetwork trainNNFromImageList(std::vector<std::string> img_file_list)
{
	NeuralNetwork nn;
	for (std::vector<std::string>::iterator iter = img_file_list.begin(); iter != img_file_list.end(); ++iter) {
		Image img(*iter);
		nn.train(img);
	}
	return nn;
}

std::vector<std::string> getImagePathList(const std::string& root)
{
	std::vector<std::string> img_file_list;
	return img_file_list;
}

uint32_t getImageClassification(NeuralNetwork& nn, const std::string& img_file)
{
	Image img(img_file);
	return nn.process(img);
}

int main(int argc, char **argv) {
	std::cout << "NN Image classification";

	// Train NN given a list of images as training data
	std::string training_image_root;
	std::vector<std::string> training_file_list = getImagePathList(training_image_root);
	NeuralNetwork nn = trainNNFromImageList(training_file_list);

	// Test the NN given a list of test images
	std::string test_image_root;
	std::vector<std::string> test_file_list = getImagePathList(test_image_root);
	for (std::vector<std::string>::iterator iter = test_file_list.begin(); iter != test_file_list.end(); ++iter) {
		uint32_t output = getImageClassification(nn, *iter);
		std::cout << "Img: " << iter->c_str() << " classified as: " << output << std::endl;
	}
	return 0;
}
