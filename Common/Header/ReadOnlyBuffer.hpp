#ifndef ReadOnlyBuffer_hpp
#define ReadOnlyBuffer_hpp

#include "Buffer.hpp"

class ReadOnlyBuffer: public Buffer {
public:
    std::string Read();
};

#endif
