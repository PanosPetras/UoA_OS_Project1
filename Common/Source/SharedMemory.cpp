#include "SharedMemory.hpp"
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "Constants.hpp"
#include <stdexcept>

SharedMemory::SharedMemory() { }

SharedMemory::~SharedMemory() {
    shm_unlink(name.c_str());
}

void SharedMemory::Initialize(
    std::string name
){
    this->name = name;

    // Create the shared memory object
    smfd = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);

    // Configure the size of the shared memory object
    ftruncate(smfd, Constants::bufferSize);

    // Memory map the shared memory object
    memory = (char*)mmap(0, Constants::bufferSize, PROT_WRITE | PROT_READ, MAP_SHARED, smfd, 0);
}

void SharedMemory::Open(
    std::string name
){
    this->name = name;

    // Open the shared memory object
    smfd = shm_open(name.c_str(), O_RDWR, 0666);

    // Memory map the shared memory object
    memory = (char*)mmap(0, Constants::bufferSize, PROT_WRITE | PROT_READ, MAP_SHARED, smfd, 0);
}

char SharedMemory::Read(
    int at
){
    if(at > Constants::bufferSize / sizeof(char)) throw std::out_of_range("Out of Bounds Index");
    return memory[at];
}

int SharedMemory::Write(
    int at, 
    char c
){
    if(at > Constants::bufferSize / sizeof(char)) throw std::out_of_range("Out of Bounds Index");

    memory[at] = c;
    return 0;
}

char* SharedMemory::operator[](
    int index
){
    if(index > Constants::bufferSize / sizeof(char)) throw std::out_of_range("Out of Bounds Index");
    return &memory[index];
}