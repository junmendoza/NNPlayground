
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <dirent.h>
using namespace std;

static const uint32_t IMAGE_WIDTH = 16;
static const uint32_t IMAGE_HEIGHT = 16;

class Image
{
public:
	Image(const std::string& img_file) : image_name(img_file)
	{
		// Todo:
		//	* Implement load image
		// 	* Set width, height and normalised bitmap data
		// 	* https://stackoverflow.com/questions/1918263/reading-pixels-of-image-in-c
		width = 0;
		height = 0;
		is_valid_image = false;
	}
	~Image(){}

public:
	std::string getName() const {
		return image_name;
	}
	bool isValidImage() const {
		return is_valid_image;
	}

	std::vector<double> getNormalisedBitmap() const {
		return bitmap;
	}

private:
	uint32_t width;
	uint32_t height;
	bool is_valid_image;
	std::string image_name;
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

void trainNNFromImageList(NumberClassifierNN &nn, std::vector<Image> image_list)
{
	for (std::vector<Image>::iterator iter = image_list.begin(); iter != image_list.end(); ++iter) {
		nn.train(*iter);
	}
}

std::vector<Image> getImageList(const std::string& root)
{
	std::vector<Image> image_list;

	struct dirent *entry = NULL;
	DIR* dir = opendir(root.c_str());
	if (dir != NULL) {
		while ((entry = readdir(dir))) {
			Image img(std::string(entry->d_name));
			if (img.isValidImage()) {
				image_list.push_back(img);
			}
		}
	}
	closedir(dir);
	return image_list;
}

uint32_t getImageClassification(NumberClassifierNN& nn, const Image& image)
{
	return nn.process(image);
}

int main(int argc, char **argv) {
	std::cout << "NN Image classification";
	std::string root = "/nnclassify";

	// Train NN given a list of images as training data
	NumberClassifierNN nn(IMAGE_WIDTH, IMAGE_HEIGHT);
	std::string training_image_root = root + "/training_set";
	const uint32_t image_count = 9;
	for (uint32_t n = 0; n < image_count; ++n) {
		std::stringstream ss;
		ss << n;
		std::string cat_root = training_image_root + "/" + ss.str();
		std::vector<Image> training_image_list = getImageList(cat_root);
		trainNNFromImageList(nn, training_image_list);
	}

	// Test the NN given a list of test images
	std::string test_image_root = root + "/test";
	std::vector<Image> test_image_list = getImageList(test_image_root);
	for (std::vector<Image>::iterator iter = test_image_list.begin(); iter != test_image_list.end(); ++iter) {
		uint32_t output = getImageClassification(nn, *iter);
		std::cout << "Image: " << iter->getName().c_str() << " classified as: " << output << std::endl;
	}
	return 0;
}
