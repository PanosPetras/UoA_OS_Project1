#include "SharedMemory.hpp"

int main(){
    auto sm = SharedMemory();
    sm.Initialize("bb");

    return 0;
}