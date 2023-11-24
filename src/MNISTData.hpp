//
//  MNISTData.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 15/11/2023.
//

#ifndef MNISTData_hpp
#define MNISTData_hpp

#include <cstring>
#include "Utils.hpp"


class MNISTData
{

static const uint32_t MNIST_IMAGE_FILE_ID   = 0x00000803;
static const uint32_t MNIST_LABEL_FILE_ID   = 0x00000801;
static const uint32_t MNIST_IMAGE_WIDTH     = 28;
static const uint32_t MNIST_IMAGE_HEIGHT    = 28;
    
struct ImageHeader
{
    int magic_number; // Compare with header constant
    int items;        // Compare with label count
    int rows;         // Num rows per image
    int colums;       // Num cols per image
};

struct LabelHeader
{
    int magic_number; // Compare with training/inference header constant
    int items;        // Compare with image count
};
    
public:
    MNISTData(const std::string& image_path_filename,
              const std::string& label_path_filename);
    ~MNISTData(void);
public:
    bool loadData(void);
    std::vector<uint8_t> getLabel(void) const {return label_data; }
    std::vector<float> getActivation(void) const { return activation_data; }
    
private:
    bool loadRawImageData(void);
    bool loadRawLabelData(void);
    bool loadImageData(void);
    bool loadLabelData(void);
    bool validateMNISTFile() const;
    std::vector<float> normalizeData(void);

private:
    std::string image_file;
    std::string label_file;

    ImageHeader* image_header;
    LabelHeader* label_header;

    uint8_t* raw_image_data;
    uint8_t* raw_label_data;

    std::vector<uint8_t> label_data;
    std::vector<float> activation_data;
};

#endif /* MNISTData_hpp */
