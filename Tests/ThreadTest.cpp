#include "Thread.hpp"
#include <iostream>

void* printHello(
    void* args
) {
    std::string message = *(std::string*)args;
    std::cout << message << std::endl;

    return nullptr;
}

int main(){
    std::string message = "This is a message printed by the child thread";

    Thread thread(
        &printHello,
        &message
    );

    thread.Start();
    thread.Join();

    std::cout << "Child thread Joined to parent thread" << std::endl;

    return 0;
}