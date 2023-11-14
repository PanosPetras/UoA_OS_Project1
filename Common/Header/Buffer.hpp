#ifndef Buffer_hpp
#define Buffer_hpp

#include "Semaphore.hpp"
#include "SharedMemory.hpp"
#include <string>

class Buffer {
protected:
    Semaphore readSemaphore, writeSemaphore, availabilitySemaphore;
    SharedMemory sharedMemory;

public:
    void Initialize(
        std::string readSemaphoreName,
        std::string writeSemaphoreName,
        std::string availabilitySemaphoreName,
        std::string sharedMemoryName
    );

    void Open(
        std::string readSemaphoreName,
        std::string writeSemaphoreName,
        std::string availabilitySemaphoreName,
        std::string sharedMemoryName
    );
};

#endif
