#include "WriteOnlyBuffer.hpp"
#include <string>
#include <iostream>

void* SenderThread(void* buffer) {
    auto wBuff = (WriteOnlyBuffer*)buffer;
    std::string message = "";

    while(true) {
        std::getline(std::cin, message);
        
        wBuff->Write(message);

        if(message == "#BYE#") exit(EXIT_SUCCESS);
    }

    return nullptr;
}