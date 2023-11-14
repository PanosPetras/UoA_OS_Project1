#include "Semaphore.hpp"
#include <fcntl.h>
#include <stdio.h>

#define PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

Semaphore::Semaphore() {
    semaphore = nullptr;
}

Semaphore::~Semaphore() {
    if(semaphore == nullptr) return;
    
    if(sem_close(semaphore) < 0)
        perror("Failed to close semaphore");

    if(wasInitialized)
        if(sem_destroy(semaphore) < 0)
            perror("Failed to destroy semaphore");
}

void Semaphore::Initialize(
    std::string name,
    int initialValue
) {
    semaphore = sem_open(name.c_str(), O_CREAT, PERMS, initialValue);
    wasInitialized = true;

    if(semaphore == SEM_FAILED) { 
        perror("Failed to initialize semaphore");
        exit(EXIT_FAILURE);
    }
}

void Semaphore::Open(
    std::string name
) {
    semaphore = sem_open(name.c_str(), O_RDWR);
    wasInitialized = false;

    if(semaphore == SEM_FAILED) { 
        perror("Failed to open semaphore");
        exit(EXIT_FAILURE);
    }
}

int Semaphore::Wait() {
    return sem_wait(semaphore);
}

int Semaphore::Post() {
    return sem_post(semaphore);
}

int Semaphore::Value() {
    int val = -1;
    sem_getvalue(semaphore, &val);

    return val;
}