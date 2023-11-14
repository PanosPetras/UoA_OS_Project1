#ifndef WriteOnlyBuffer_hpp
#define WriteOnlyBuffer_hpp

#include "Buffer.hpp"

class WriteOnlyBuffer: public Buffer {
public:
    void Write(std::string message);
};

#endif
