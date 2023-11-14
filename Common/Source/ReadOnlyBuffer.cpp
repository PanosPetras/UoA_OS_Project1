#include "ReadOnlyBuffer.hpp"
#include "Constants.hpp"

std::string ReadOnlyBuffer::Read() {
    std::string message = "";
    std::string bufferContent = "";
    bool messageHasEnded = false;

    while (!messageHasEnded) {
        readSemaphore.Wait();
        availabilitySemaphore.Wait();

        for(int i = 0; i < Constants::bufferSize / sizeof(char); i++){
            if(sharedMemory.Read(i) == '\0'){
                messageHasEnded = true;
                break;
            }

            message += sharedMemory.Read(i);
        }

        writeSemaphore.Post();
        availabilitySemaphore.Post();
    }

    return message;
}