#include "ReadOnlyBuffer.hpp"
#include <string>
#include <iostream>

void* ReceiverThread(void* buffer){
    auto wBuff = (ReadOnlyBuffer*)buffer;

    while (true) {
        std::string message = wBuff->Read();

        std::cout << message << std::endl;

        if(message == "#BYE#") pthread_exit(NULL);
    }

    return nullptr;
}