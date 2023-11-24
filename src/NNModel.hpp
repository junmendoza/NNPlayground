//
//  NNModel.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#ifndef NNModel_hpp
#define NNModel_hpp

#include <vector>

class NNModel
{
public:
    NNModel(void);
    ~NNModel(void);
    
public:
    uint32_t train(std::vector<float>& training_data, std::vector<uint8_t> label);
    void infer(std::vector<float>& inference_data, std::vector<uint8_t> label);
    
};

#endif /* NNModel_hpp */
