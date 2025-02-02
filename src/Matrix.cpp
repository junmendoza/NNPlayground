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
//#define DEBUGME
#ifdef DEBUGME
    //setDefaultTestValuesByRow();
    setDefaultTestValuesByCol();
    print(10, 10);
#endif
}

void MatrixMN::setDefaultValue(double val)
{
    for (size_t c = 0; c < _cols; ++c) {
        for (size_t r = 0; r < _rows; ++r) {
            _data[r][c] = val;
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

VectorN MatrixMN::mul(const VectorN& vec)
{
    assert(vec._size == _rows);
    VectorN new_vec(vec._size);
    size_t r, c;
    for (r = 0; r < _rows; ++r) {
        double accumulate = 0.0f;
        for (c = 0; c < _cols; ++c) {
            accumulate = accumulate + (vec._data[c] * _data[r][c]);
        }
        new_vec._data[r] = accumulate;
    }
    return new_vec;
}

VectorN MatrixMN::operator*(const VectorN& rhs)
{
    return mul(rhs);
}

}
