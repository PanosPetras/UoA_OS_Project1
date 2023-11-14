#ifndef Semaphore_hpp
#define Semaphore_hpp

#include <string>
#include <semaphore.h>

class Semaphore {
protected:
    sem_t *semaphore;

    bool wasInitialized;

public:
    Semaphore();
    ~Semaphore();
    
    // Initialization
    void Initialize(
        std::string name,
        int initialValue
    );
    void Open(
        std::string name
    );

    int Wait();
    int Post();
    int Value();
};

#endif
