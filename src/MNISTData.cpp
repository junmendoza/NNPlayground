//
//  MNISTData.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 15/11/2023.
//

#include <fstream>
#include "MNISTData.hpp"

MNISTData::MNISTData(const std::string& image_path_filename,
                     const std::string& label_path_filename)
    : _image_file(image_path_filename),
      _label_file(label_path_filename)
{
}

MNISTData::~MNISTData(void)
{
    SAFE_DELETE(_image_header);
    SAFE_DELETE(_label_header);
    SAFE_DELETE_ARRAY(_raw_image_data);
    SAFE_DELETE_ARRAY(_raw_label_data);
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
    if (NULL == _image_header) {
        return false;
    }
    if (NULL == _label_header) {
        return false;
    }
    return  MNIST_IMAGE_FILE_ID == _image_header->magic_number &&
            MNIST_IMAGE_HEIGHT  == _image_header->rows &&
            MNIST_IMAGE_WIDTH   == _image_header->colums &&
            _image_header->items == _label_header->items;
}

void MNISTData::normalizeData(void)
{
    assert(NULL != _raw_image_data);
    uint32_t raw_data_idx = 0;
    for (uint32_t i = 0; i < _image_header->items; ++i) {
        double* normalized_data = new double[PIXELS_PER_IMAGE];
        for (uint32_t j = 0; j < PIXELS_PER_IMAGE; ++j) {
            double activation = ((double)_raw_image_data[++raw_data_idx]) / 255.0f;
            normalized_data[j] = activation;
        }
        _activation_data.push_back(normalized_data);
    }
}

bool MNISTData::loadRawImageData(void)
{
    std::ifstream file(_image_file, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // Load header
    _image_header = new ImageHeader;
    const uint32_t header_size = sizeof(ImageHeader);
    file.read((char*)_image_header, header_size);
    if (!file) {
        return false;
    }
    
    // Twist header
    _image_header->magic_number = TWIST32(_image_header->magic_number);
    _image_header->items        = TWIST32(_image_header->items);
    _image_header->rows         = TWIST32(_image_header->rows);
    _image_header->colums       = TWIST32(_image_header->colums);
    
    // Load data
    const uint32_t data_size8 = _image_header->items * _image_header->rows * _image_header->colums;
    _raw_image_data = new uint8_t[data_size8];
    file.read((char*)_raw_image_data, data_size8);
    if (!file) {
        return false;
    }
    
    // Twist data
    const uint32_t data_size32 = data_size8 / 4;
    for (int n = 0; n < data_size32; ++n) {
        *((uint32_t*)(_raw_image_data + n*4)) = TWIST32(*((uint32_t*)(_raw_image_data + n*4)));
        //printf("0x%.8X, ", *((uint32_t*)(_raw_image_data + n*4)));
    }
    return true;
}

bool MNISTData::loadRawLabelData(void)
{
    std::ifstream file(_label_file, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // Load header
    _label_header = new LabelHeader;
    file.read((char*)_label_header, sizeof(LabelHeader));
    if (!file) {
        return false;
    }
    _label_header->magic_number = TWIST32(_label_header->magic_number);
    _label_header->items        = TWIST32(_label_header->items);
    
    // Load data
    const uint32_t data_size8 = _label_header->items;
    _raw_label_data = new uint8_t[data_size8];
    file.read((char*)_raw_label_data, data_size8);
    if (!file) {
        return false;
    }

    // Twist data
    const uint32_t data_size32 = data_size8 / 4;
    for (int n = 0; n < data_size32; ++n) {
        *((uint32_t*)(_raw_label_data + n*4)) = TWIST32(*((uint32_t*)(_raw_label_data + n*4)));
        //printf("0x%.8X, ", *((uint32_t*)(_raw_label_data + n*4)));
    }
    return true;
}

bool MNISTData::loadImageData(void)
{
    if (!loadRawImageData()) {
        return false;
    }
    return true;
}

bool MNISTData::loadLabelData(void)
{
    if (!loadRawLabelData()) {
        return false;
    }
    return true;
}

