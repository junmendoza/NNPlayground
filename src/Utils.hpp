//
//  Utils.hpp
//  NNPlayground
//
//  Created by Jun Mendoza on 12/11/2023.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <string>
#include <stdlib.h>
#include <time.h>


#define UNUSED(x) (void)x;
#define SAFE_DELETE(ptr) if (NULL != ptr) { delete ptr; ptr = NULL; }
#define SAFE_DELETE_ARRAY(ptr) if (NULL != ptr) { delete[] ptr; ptr = NULL; }

// Twist 4 bytes within a 32-bit word
// byte0 -> byte3
// byte1 -> byte2
// byte2 -> byte1
// byte0 -> byte3
#define TWIST32(n) ((n & 0xff000000) >> 24) | ((n & 0x00ff0000) >> 8)| ((n & 0x0000ff00) << 8) | ((n & 0x000000ff) << 24)

namespace Utils {

size_t randomizeUint(size_t min, size_t max);
double randomizeDouble01(void);
void testRandomizeUint(void);
void testRandomizeDouble(void);

class Trace
{
public:
    static void strace(const char* format, ...) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }

private:
enum TraceDest
{
    file,
    stdout,
    stderr
};

public:
    Trace(const std::string& dest, const std::string& prefix_ident);
    ~Trace();

    void trace(const char* format, ...);
    void trace_err(const char* format, ...);
    void trace_file(const char* format, ...);

private:
    TraceDest trace_dest;
    std::string dest_file;
    std::string prefix;

};

}


#endif /* Utils_hpp */
