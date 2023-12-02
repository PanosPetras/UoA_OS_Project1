#include "Thread.hpp"
#include <pthread.h>
#include <stdexcept>
#include <system_error>
#include <iostream>

Thread::Thread(
    void* (*func)(void*),
    void* arg
){
    this->func = func;
    this->arg = arg;
    isStarted = false;
    isJoined = false;
}

void Thread::Start() {
    if(isStarted) return;
    isStarted = true;

    if(pthread_create(
        &threadId,
        NULL, 
        func, 
        arg
    ) != 0)
        throw std::system_error(EAGAIN, std::generic_category(), "Failed to start thread");
}

void* Thread::Join() {
    if(isJoined) return nullptr;
    isJoined = true;

    void* returnValue;

    if(pthread_join(threadId, &returnValue) != 0)
        std::cerr << "Failed to join thread" << std::endl;

    return returnValue;
}

void Thread::Cancel() {
    pthread_cancel(threadId);
}