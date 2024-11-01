 /**
 * @file consumer.cpp
 * @author Annika Hall
 * @brief The producer in the producer and consumer problem
 * @date 2024-11-01
 * 
 */

#include "../include/consumer.hpp"
#include "../include/membuff.hpp"

/**
 * @brief The main function for the consumer
 * 
 * @param argc The number of arguments fed into the program
 * @param argv Array to hold the command line-fed arguments, used for the shared memory file name
 * @return int Exit status of the program
 */
int main(int argc, char *argv[]) {
    // Variables
    int fd;
    const char *shmpath = argv[1];
    struct sharedMem *consMem;

    // Open shared memory
    fd = shm_open(shmpath, O_RDWR, 0);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    // Set shared memory size
    if (ftruncate(fd, sizeof(*consMem)) == -1) {
        perror("ftruncate failed");
        return 1;
    }

    // Map shared memory to local address space
    consMem = static_cast<sharedMem*>(mmap(NULL, sizeof(*consMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (consMem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    for (int i = 5; i > 0; --i) {
        // Wait until buffer has items and mutex is available
        sem_wait(&(consMem->full));
        sem_wait(&(consMem->mutex));

        // Retrieve item from buffer
        int consumed_value = consMem->table[consMem->out];
        std::cout << "Consumed: " << consumed_value << std::endl;

        // Update buffer index with wrapping
        consMem->out = (consMem->out + 1) % TABLE_SIZE;

        // Release mutex and signal buffer space availability
        sem_post(&(consMem->mutex));
        sem_post(&(consMem->empty));

        // Simulate variable consumption time
        sleep(rand() % 10);
    }

    // Detach shared memory
    shm_unlink(shmpath);

    return 0;
}
