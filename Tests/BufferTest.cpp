#include "ReadOnlyBuffer.hpp"
#include "WriteOnlyBuffer.hpp"
#include <iostream>

int main(){
    auto wbuf = WriteOnlyBuffer();
    wbuf.Initialize("test_semaphore_onez", "test_semaphore_twoz", "test_semaphore_threez", "shm_one");

    // More than 15 characters and this test case will freeze waiting for someone to 
    // consume the contents of the buffer, which will never happen in this instance
    wbuf.Write("Hello There!\n");

    auto rbuf = ReadOnlyBuffer();
    rbuf.Open("test_semaphore_onez", "test_semaphore_twoz", "test_semaphore_threez", "shm_one");

    auto message = rbuf.Read();

    std::cout << message;

    return 0;
}