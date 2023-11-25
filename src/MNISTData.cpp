//
//  MNISTData.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 15/11/2023.
//

#include <fstream>
#include "MNISTData.hpp"

MNISTData::MNISTData(const std::string& image_path_filename,
                     const std::string& labelpath_filename)
    : image_file(image_path_filename),
      label_file(labelpath_filename)
{
}

MNISTData::~MNISTData(void)
{
    SAFE_DELETE(image_header);
    SAFE_DELETE(label_header);
    SAFE_DELETE_ARRAY(raw_image_data);
    SAFE_DELETE_ARRAY(raw_label_data);
}

bool MNISTData::loadData(void)
{
    if (!loadImageData()) {
        return false;
    }
    if (!loadLabelData()) {
        return false;
    }
    if (!validateMNISTFile()) {
        return false;
    }
    normalizeData();
    return true;
}


bool MNISTData::validateMNISTFile() const
{
    if (NULL == image_header) {
        return false;
    }
    if (NULL == label_header) {
        return false;
    }
    return  MNIST_IMAGE_FILE_ID == image_header->magic_number &&
            MNIST_IMAGE_HEIGHT  == image_header->rows &&
            MNIST_IMAGE_WIDTH   == image_header->colums &&
            image_header->items == label_header->items;
}

void MNISTData::normalizeData(void)
{
    assert(NULL != raw_image_data);
    for (uint32_t n = 0; n < image_header->items; ++n) {
        float activation = ((float)raw_image_data[n]) / 255.0f;
        activation_data.push_back(activation);
    }
}

bool MNISTData::loadRawImageData(void)
{
    std::ifstream file(image_file, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // Load header
    image_header = new ImageHeader;
    const uint32_t header_size = sizeof(ImageHeader);
    file.read((char*)image_header, header_size);
    if (!file) {
        return false;
    }
    
    // Twist header
    image_header->magic_number = TWIST32(image_header->magic_number);
    image_header->items        = TWIST32(image_header->items);
    image_header->rows         = TWIST32(image_header->rows);
    image_header->colums       = TWIST32(image_header->colums);
    
    // Load data
    const uint32_t data_size8 = image_header->items * image_header->rows * image_header->colums;
    raw_image_data = new uint8_t[data_size8];
    file.read((char*)raw_image_data, data_size8);
    if (!file) {
        return false;
    }
    
    // Twist data
    const uint32_t data_size32 = data_size8 / 4;
    for (int n = 0; n < data_size32; ++n) {
        *((uint32_t*)(raw_image_data + n*4)) = TWIST32(*((uint32_t*)(raw_image_data + n*4)));
        //printf("0x%.8X, ", *((uint32_t*)(raw_image_data + n*4)));
    }
    return true;
}

bool MNISTData::loadRawLabelData(void)
{
    std::ifstream file(label_file, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // Load header
    label_header = new LabelHeader;
    file.read((char*)label_header, sizeof(LabelHeader));
    if (!file) {
        return false;
    }
    label_header->magic_number = TWIST32(label_header->magic_number);
    label_header->items        = TWIST32(label_header->items);
    
    // Load data
    const uint32_t data_size8 = label_header->items;
    raw_label_data = new uint8_t[data_size8];
    file.read((char*)raw_label_data, data_size8);
    if (!file) {
        return false;
    }

    // Twist data
    const uint32_t data_size32 = data_size8 / 4;
    for (int n = 0; n < data_size32; ++n) {
        *((uint32_t*)(raw_label_data + n*4)) = TWIST32(*((uint32_t*)(raw_label_data + n*4)));
        //printf("0x%.8X, ", *((uint32_t*)(raw_label_data + n*4)));
    }

    label_data.assign(raw_label_data, raw_label_data + data_size8);
    return true;
}

bool MNISTData::loadImageData(void)
{
    if (!loadRawImageData()) {
        return false;
    }
    // raw_image_data
    return true;
}

bool MNISTData::loadLabelData(void)
{
    if (!loadRawLabelData()) {
        return false;
    }
    // raw_label_data
    return true;
}

