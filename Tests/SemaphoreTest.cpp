#include "Semaphore.hpp"

int main(){
    const std::string name = "test_semaphore";

    auto initialSem = Semaphore();
    initialSem.Initialize(
        name, 
        0
    );
    
    auto openedSem = Semaphore();
    openedSem.Open(
        name
    );

    initialSem.Post();
    openedSem.Wait();

    openedSem.Post();
    initialSem.Wait();

    return 0;
}