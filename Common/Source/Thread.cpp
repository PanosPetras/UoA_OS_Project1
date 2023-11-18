#include "Thread.hpp"

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

    pthread_create(
        &threadId,
        NULL, 
        func, 
        arg
    );
}

void Thread::Join() {
    if(isJoined) return;
    isJoined = true;

    pthread_join(threadId, nullptr);
}