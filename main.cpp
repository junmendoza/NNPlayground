
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

static const uint32_t IMAGE_WIDTH = 16;
static const uint32_t IMAGE_HEIGHT = 16;

class Image
{
public:
	Image(const std::string& img_file)
	{
		// Todo:
		//	* Implement load image
		// 	* Set width, height and normalised bitmap data
		width = 0;
		height = 0;

	}
	~Image(){}

	std::vector<double> getNormalisedBitmap() const {
		return bitmap;
	}

private:
	uint32_t width;
	uint32_t height;
	std::vector<double> bitmap;
};

class NumberClassifierNN
{
public:
	NumberClassifierNN(uint32_t img_width, uint32_t img_height) :
		input_neurons(img_width* img_height)
	{
	}
	~NumberClassifierNN(){}

public:
	bool train(const Image& img)
	{
		// Todo: Implement the following
		// 	* Setup input neuron
		//	* Setup middle layers
		//	* Train until recognised
		//	* Save weights and bias
		std::vector<double> bitmap = img.getNormalisedBitmap();
		assert(bitmap.size() == input_neurons);
		return true;
	}

	uint32_t process(const Image& img)
	{
		// Todo: Implement the following
		// 	* Setup input neuron
		//	* Setup middle layers
		//	* Feed img bitmap to nn
		//	* Return nn output
		return output;
	}

private:
	uint32_t input_neurons;
	uint32_t output;
};

NumberClassifierNN trainNNFromImageList(std::vector<std::string> img_file_list)
{
	NumberClassifierNN nn(IMAGE_WIDTH, IMAGE_HEIGHT);
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

uint32_t getImageClassification(NumberClassifierNN& nn, const std::string& img_file)
{
	Image img(img_file);
	return nn.process(img);
}

int main(int argc, char **argv) {
	std::cout << "NN Image classification";

	// Train NN given a list of images as training data
	std::string training_image_root;
	std::vector<std::string> training_file_list = getImagePathList(training_image_root);
	NumberClassifierNN nn = trainNNFromImageList(training_file_list);

	// Test the NN given a list of test images
	std::string test_image_root;
	std::vector<std::string> test_file_list = getImagePathList(test_image_root);
	for (std::vector<std::string>::iterator iter = test_file_list.begin(); iter != test_file_list.end(); ++iter) {
		uint32_t output = getImageClassification(nn, *iter);
		std::cout << "Img: " << iter->c_str() << " classified as: " << output << std::endl;
	}
	return 0;
}
