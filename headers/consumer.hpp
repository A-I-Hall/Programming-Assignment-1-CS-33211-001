/**
 * @file consumer.hpp
 * @author Annika Hall
 * @brief Header file for the consumer in the producer/consumer problem
 * @date 2024-11-01
 */

#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>

// Function declaration for the main consumer function
int main(int argc, char **argv);

#endif // CONSUMER_HPP
