#include "ReceiverThread.hpp"
#include "SenderThread.hpp"
#include "Constants.hpp"
#include "Thread.hpp"
#include <iostream>

int main() {
    auto rBuff = ReadOnlyBuffer();
    auto wBuff = WriteOnlyBuffer();

    try {
        rBuff.Initialize(
            std::string(Constants::processAReadSem),
            std::string(Constants::processBWriteSem),
            std::string(Constants::availabilitySem1),
            std::string(Constants::shmSegment1)
        );

        wBuff.Initialize(
            std::string(Constants::processBReadSem),
            std::string(Constants::processAWriteSem),
            std::string(Constants::availabilitySem2),
            std::string(Constants::shmSegment2)
        );
    } catch(...) {
        std::cerr << "Failed to initialize buffers" << std::endl;
        exit(EXIT_FAILURE);
    }

    Thread senderThread = Thread(&SenderThread, &wBuff),
            receiverThread(&ReceiverThread, &rBuff);
    
    try {
        senderThread.Start();
        receiverThread.Start();
    } catch(...) {
        std::cerr << "Failed to start I/O threads" << std::endl;
        exit(EXIT_FAILURE);
    }

    senderThread.Join();
    receiverThread.Join();
}