#ifndef Thread_hpp
#define Thread_hpp

typedef unsigned long int pthread_t;

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
    void* Join();

    void Cancel();
};

#endif