/**
 * @file membuff.hpp
 * @author Annika Hall
 * @brief The shared memory buffer for the producer/consumer probelm
 * @date 2024-11-01
 * 
 */

#ifndef MEMBUFF_HPP
#define  MEMBUFF_HPP
    #include <stdlib.h>
    #include <sys/shm.h>
    #include <sys/ipc.h>
    #include <semaphore.h>

    /**
     * @brief The size of the buffer
     */
    #define TABLE_SIZE 2


    /**
     * @brief The shared memory buffer with semaphores
     */
    struct sharedMem {

        int table[TABLE_SIZE];

        int in;
        int out;

        sem_t mutex;
        sem_t empty;
        sem_t full;

    };


#endif
