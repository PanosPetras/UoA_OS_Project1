#ifndef SharedMemory_hpp
#define SharedMemory_hpp

#include <string>

class SharedMemory {
protected:
    //Shared Memory File Descriptor
    int smfd;
    
    std::string name;
    char *memory;

public:
    SharedMemory();
    ~SharedMemory();

    // Initialization
    void Initialize(
        std::string name
    );
    void Open(
        std::string name
    );

    // IO
    char Read(
        int at
    );
    int Write(
        int at, 
        char c
    );

    char* operator[](
        int index
    );
};

#endif
