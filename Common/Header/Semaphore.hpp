#ifndef Semaphore_hpp
#define Semaphore_hpp

#include <string>
#include <semaphore.h>

class Semaphore {
protected:
    sem_t *semaphore;

    std::string name;

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

    void Wait();
    void Post();
    int Value();
};

#endif
