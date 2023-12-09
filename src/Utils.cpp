//
//  Utils.cpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#include "Utils.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <dirent.h>

namespace Utils {

size_t randomizeUint(size_t min, size_t max)
{
    assert(max > min);
    size_t n = rand()% (max+1-min);
    n = min + n;
    return n;
}

double randomizeDouble01(void)
{
    size_t max = 10;
    size_t n = rand()% max+1;
    return 1.0f / (double)n;
}

void testRandomizeUint(void)
{
    Trace::strace("Randomize uint start.\n");
    for(size_t n = 0; n < 100; ++n) {
        size_t r = randomizeUint(0, 20);
        Trace::strace("Uint: %d\n", r);
    }
    Trace::strace("Randomize uint end.\n");
}

void testRandomizeDouble(void)
{
    Trace::strace("Randomize double start.\n");
    for(size_t n = 0; n < 100; ++n) {
        double r = randomizeDouble01();
        Trace::strace("Double: %f\n", r);
    }
    Trace::strace("Randomize double end.\n");
}

Trace::Trace(const std::string& dest, const std::string& prefix_ident) :
    dest_file(dest),
    prefix(prefix_ident)
{
}

Trace::~Trace()
{   
}

void Trace::trace(const char* format, ...)
{
    // Todo: make this a dynamic size string buffer
    char buffer[512];
    va_list args;
    va_start(args, format);
    vsprintf(buffer,format, args);
    std::cout << prefix << ": " << buffer;
    va_end(args);
}

void Trace::trace_err(const char* format, ...)
{
}

void Trace::trace_file(const char* format, ...)
{
}

}

