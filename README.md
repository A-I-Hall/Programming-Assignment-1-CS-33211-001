Author: Annika Hall
Course: CS-33211: Operating Systems
Instructor: Dr. Qiang Guan
Semester: Fall 2024
University: Kent State University

Description
The producer generates items and places them onto a shared table, while the consumer picks up these items. The table has a limited capacity of two items at a time. When the table is full, the producer will wait until space is available. Conversely, when there are no items on the table, the consumer will wait. Semaphores are used for synchronization between the producer and consumer, ensuring mutual exclusion. Both programs utilize threads and share memory for the table.

Implementation
Each of the producer and consumer has its own process, with a dedicated thread for each that points to functions named producer and consumer, respectively. The shared memory buffer has a capacity of two items. To prevent deadlock and data hazards associated with this shared buffer, semaphores are employed to indicate its status. A semaphore value of 1 indicates that the buffer is in use, while a value of 0 signifies that the buffer is available.

Compilation
The producer and consumer are separate files intended to function as distinct processes. 

make consumer - Compiles the consumer program.
make producer - Compiles the producer program.
make clean - Removes any object (.o) files and the compiled program files.
make run - Compiles both the producer and consumer and runs them with the shared memory key of shm.
