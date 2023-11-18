#include "ReceiverThread.hpp"
#include "SenderThread.hpp"
#include "Constants.hpp"
#include "Thread.hpp"
#include <iostream>

int main() {
    auto rBuff = ReadOnlyBuffer();
    rBuff.Initialize(
        std::string(Constants::processAReadSem),
        std::string(Constants::processBWriteSem),
        std::string(Constants::availabilitySem1),
        std::string(Constants::shmSegment1)
    );

    auto wBuff = WriteOnlyBuffer();
    wBuff.Initialize(
        std::string(Constants::processBReadSem),
        std::string(Constants::processAWriteSem),
        std::string(Constants::availabilitySem2),
        std::string(Constants::shmSegment2)
    );

    Thread senderThread = Thread(&SenderThread, &wBuff),
            receiverThread(&ReceiverThread, &rBuff);
    
    senderThread.Start();
    receiverThread.Start();

    senderThread.Join();
    receiverThread.Join();
}