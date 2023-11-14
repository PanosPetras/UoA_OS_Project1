#ifndef Constants_hpp
#define Constants_hpp

#include <string>

class Constants {
public:
    // Shared Memory names
    static constexpr std::string_view shmSegment1 = "shared_memory_segment_one";
    static constexpr std::string_view shmSegment2 = "shared_memory_segment_two";

    //Semaphore names
    static constexpr std::string_view processAWriteSem = "process_a_write_sem";
    static constexpr std::string_view processAReadSem = "process_a_read_sem";
    static constexpr std::string_view availabilitySem1 = "availability_sem_one";
    static constexpr std::string_view processBWriteSem = "process_b_write_sem";
    static constexpr std::string_view processBReadSem = "process_b_read_sem";
    static constexpr std::string_view availabilitySem2 = "availability_sem_two";

    static constexpr int bufferSize = 15 * sizeof(char);
};

#endif
