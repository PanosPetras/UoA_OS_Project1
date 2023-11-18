#include "ReceiverThread.hpp"
#include "SenderThread.hpp"
#include "Constants.hpp"
#include "Thread.hpp"
#include <pthread.h>
#include <iostream>

int main() {
    auto rBuff = ReadOnlyBuffer();
    rBuff.Open(
        std::string(Constants::processBReadSem),
        std::string(Constants::processAWriteSem),
        std::string(Constants::availabilitySem2),
        std::string(Constants::shmSegment2)
    );

    auto wBuff = WriteOnlyBuffer();
    wBuff.Open(
        std::string(Constants::processAReadSem),
        std::string(Constants::processBWriteSem),
        std::string(Constants::availabilitySem1),
        std::string(Constants::shmSegment1)
    );

    Thread senderThread = Thread(&SenderThread, &wBuff),
            receiverThread(&ReceiverThread, &rBuff);
    
    senderThread.Start();
    receiverThread.Start();

    senderThread.Join();
    receiverThread.Join();
}