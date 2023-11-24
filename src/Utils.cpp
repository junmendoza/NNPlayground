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

