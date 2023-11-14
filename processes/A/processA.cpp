#include "ReceiverThread.hpp"
#include "SenderThread.hpp"
#include "Constants.hpp"
#include <pthread.h>
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

    pthread_t senderThreadId, receiverThreadId;

    pthread_create(
        &senderThreadId, 
        NULL, 
        &SenderThread, 
        &wBuff
    );

    pthread_create(
        &receiverThreadId,
        NULL, 
        &ReceiverThread, 
        &rBuff
    );

    pthread_join(senderThreadId, nullptr);
    pthread_join(receiverThreadId, nullptr);
}