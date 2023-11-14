#include "WriteOnlyBuffer.hpp"
#include <vector>

void WriteOnlyBuffer::Write(
    std::string message
){    
    message += '\0';
    for(int i = 0; i < message.length() / 15 + 1; i++){
        writeSemaphore.Wait();
        availabilitySemaphore.Wait();

        for(int j = 0; j < std::min(15, static_cast<int>(message.length()) - i * 15); j++){
            sharedMemory.Write(
                j, 
                message[i * 15 + j]
            );
        }

        readSemaphore.Post();
        availabilitySemaphore.Post();
    }
}