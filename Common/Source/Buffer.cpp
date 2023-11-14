#include "Buffer.hpp"
#include "Constants.hpp"

void Buffer::Initialize(
    std::string readSemaphoreName,
    std::string writeSemaphoreName,
    std::string availabilitySemaphoreName,
    std::string sharedMemoryName
){
    // Initialize Semaphores
    readSemaphore.Initialize(
        readSemaphoreName,
        0
    );
    writeSemaphore.Initialize(
        writeSemaphoreName, 
        1
    );
    availabilitySemaphore.Initialize(
        availabilitySemaphoreName,
        1
    );

    // Initialize Shared Memory
    sharedMemory.Initialize(
        sharedMemoryName
    );
}

void Buffer::Open(
    std::string readSemaphoreName,
    std::string writeSemaphoreName,
    std::string availabilitySemaphoreName,
    std::string sharedMemoryName
){
    // Initialize Semaphores
    readSemaphore.Open(
        readSemaphoreName
    );
    writeSemaphore.Open(
        writeSemaphoreName
    );
    availabilitySemaphore.Open(
        availabilitySemaphoreName
    );

    // Initialize Shared Memory
    sharedMemory.Open(
        sharedMemoryName
    );
}
