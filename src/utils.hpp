

#ifndef utils_hpp
#define utils_hpp


#include <cassert>


// Use (void) to silent unused warnings. (from https://en.cppreference.com/w/cpp/error/assert)
#define assertm(exp, msg) assert(((void)msg, exp))


#endif