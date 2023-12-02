//
//  Matrix.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 30/11/2023.
//

#include "Matrix.hpp"
#include "Utils.hpp"

namespace Math
{

MatrixMN::MatrixMN(void)
{
}

MatrixMN::MatrixMN(size_t rows, size_t cols)
    : _rows(rows),
      _cols(cols)
{
    setup(_rows, _cols);
}

MatrixMN::~MatrixMN(void)
{
    for (size_t r = 0; r < _rows; ++r) {
        SAFE_DELETE_ARRAY(_data[r]);
    }
    SAFE_DELETE_ARRAY(_data);
}

void MatrixMN::setup(size_t rows, size_t cols)
{
    _rows = rows;
    _cols = cols;
    _data = new double*[_rows];
    for (size_t r = 0; r < _rows; ++r) {
        _data[r] = new double[_cols];
    }
    setDefaultValue();
//#define DEBUGME
#ifdef DEBUGME
    //setDefaultTestValuesByRow();
    setDefaultTestValuesByCol();
    print(10, 10);
#endif
}

void MatrixMN::setDefaultValue(void)
{
    for (size_t c = 0; c < _cols; ++c) {
        for (size_t r = 0; r < _rows; ++r) {
            _data[r][c] = DEFAULT_VAL;
        }
    }
}

void MatrixMN::setDefaultTestValuesByRow(void)
{
    double val = 0.0;
    for (size_t c = 0; c < _cols; ++c) {
        val = 0.0;
        for (size_t r = 0; r < _rows; ++r) {
            _data[r][c] = (val += 0.001);
        }
    }
}

void MatrixMN::setDefaultTestValuesByCol(void)
{
    double val = 0.0;
    for (size_t r = 0; r < _rows; ++r) {
        val = 0.0;
        for (size_t c = 0; c < _cols; ++c) {
            _data[r][c] = (val += 0.001);
        }
    }
}

void MatrixMN::print(size_t rows, size_t cols)
{
    Utils::Trace::strace("\n");
    Utils::Trace::strace("Printing matrix\n");
    Utils::Trace::strace("\n");

    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            Utils::Trace::strace("%f, ", _data[r][c]);
        }
        Utils::Trace::strace("\n");
    }
}

VectorN MatrixMN::mul(const VectorN& rhs)
{
    assert(rhs._size == _cols);
    VectorN vec(rhs._size);
    size_t c, r;
    for (c = 0; c < vec._size; ++c) {
        double accumulate = 0.0f;
        for (r = 0; r < vec._size; ++r) {
            accumulate = accumulate + (rhs._data[r] * _data[r][c]);
        }
        vec._data[r] = accumulate;
    }
    return vec;
}

VectorN MatrixMN::operator*(const VectorN& rhs)
{
    return mul(rhs);
}

}
