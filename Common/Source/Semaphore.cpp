#include "Semaphore.hpp"
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <system_error>

#define PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

Semaphore::Semaphore() {
    semaphore = nullptr;
}

Semaphore::~Semaphore() {
    if(semaphore == nullptr) return;
    
    if(sem_close(semaphore) < 0)
        std::cerr << "Failed to close semaphore" << std::endl;

    if(sem_unlink(name.c_str()) == -1)
        std::cerr << "Failed to unlink semaphore" << std::endl;
}

void Semaphore::Initialize(
    std::string name,
    int initialValue
) {
    this->name = name;
    
    semaphore = sem_open(name.c_str(), O_CREAT, PERMS, initialValue);

    if(semaphore == SEM_FAILED)
        throw std::system_error(EAGAIN, std::generic_category(), "Failed to initialize semaphore");
}

void Semaphore::Open(
    std::string name
) {
    this->name = name;

    semaphore = sem_open(name.c_str(), O_RDWR);

    if(semaphore == SEM_FAILED) 
        throw std::system_error(EAGAIN, std::generic_category(), "Failed to open semaphore");
}

void Semaphore::Wait() {
    if(sem_wait(semaphore) != 0)
        std::cerr << "Failed to wait semaphore" << std::endl;
}

void Semaphore::Post() {
    if(sem_post(semaphore) != 0)
        std::cerr << "Failed to post semaphore" << std::endl;
}

int Semaphore::Value() {
    int val = -1;
    sem_getvalue(semaphore, &val);

    return val;
}