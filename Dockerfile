 
# Use an official C++ development image
FROM gcc:latest

# Set the working directory
WORKDIR /usr/src/app

# Copy your source code to the container
COPY . .

# Install pthreads and other necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Compile the producer and consumer programs
RUN gcc producer.cpp -pthread -lrt -o producer
RUN gcc consumer.cpp -pthread -lrt -o consumer
