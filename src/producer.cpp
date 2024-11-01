/**
 * @file producer.cpp
 * @author Annika Hall
 * @brief The producer in the producer and consumer problem
 * @date 2024-11-01
 * 
 */

#include "../include/producer.hpp"
#include "../include/membuff.hpp"

/**
 * @brief The main function for the producer
 * 
 * @param argc The number of arguments fed into the program
 * @param argv Array to hold the command line fed arguments, used for the shared memory file name
 * @return int Exit status of the program
 */

int main(int argc, char *argv[]) {

    // Variables
    int fd;
    const char *shmpath = argv[1];
    struct sharedMem *prodMem;

    // Open shared memory
    fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    // Set shared memory size to struct size
    if (ftruncate(fd, sizeof(*prodMem)) == -1) {
        perror("ftruncate failed");
        return 1;
    }

    // Map shared memory
    prodMem = static_cast<sharedMem*>(mmap(NULL, sizeof(*prodMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (prodMem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // Initialize semaphores
    sem_init(&(prodMem->mutex), 1, 1);
    sem_init(&(prodMem->full), 1, 0);
    sem_init(&(prodMem->empty), 1, TABLE_SIZE);

    // Initialize buffer indices
    prodMem->in = 0;
    prodMem->out = 0;

    for (int i = 5; i > 0; --i) {
        // Wait if buffer is full or mutex is locked
        sem_wait(&prodMem->empty);
        sem_wait(&prodMem->mutex);

        int produced_value = rand();

        std::cout << "Produced: " << produced_value << std::endl;

        // Insert produced value in buffer
        prodMem->table[prodMem->in] = produced_value;

        // Increment index with wrapping
        prodMem->in = (prodMem->in + 1) % TABLE_SIZE;

        // Release mutex and signal buffer as full
        sem_post(&prodMem->mutex);
        sem_post(&prodMem->full);

        sleep(rand() % 10);
    }

    // Clean up shared memory
    shm_unlink(shmpath);

    return 0;
}
