#ifndef thread_hpp
#define thread_hpp

#include <pthread.h>

class Thread {
protected:
    pthread_t threadId;

    void* (*func)(void*);
    void* arg;

    bool isStarted, isJoined;

public:
    Thread(
        void* (*func)(void*),
        void* arg
    );

    void Start();
    void Join();
};

#endif