# Cache-Manager

The Cache-Manager is a C++ program designed to perform caching of frequently accessed items from an input file. The program handles multiple readers and writers of items, efficiently retrieves cached items, and implements an effective eviction mechanism when there is a cache miss. The program also handles the case of a dirty cache item, where a writer is modifying the item that is already cached.

## Prerequisites

- C++ compiler with C++11 support
- CMake (version 3.10 or higher)

## Building the program

1. Clone the repository:

```
git clone https://github.com/dishak11/Cache-Manager.git
```

2. Navigate to the project directory:

```
cd Cache-Manager
```

3. Create a build directory:

```
mkdir build
cd build
```

4. Run CMake to generate Makefiles:

```
cmake ..
```

5. Build the project:

```
make
```

## Running the program

```
cd src
```

After building the project, you can run the program with the following command:

```
./cache_handler <size_of_cache> <reader_file> <writer_file> <items_file>
```

- `size_of_cache`: An integer value indicating the number of elements that the cache can hold at any given time.
- `reader_file`: A file that contains a list of file names. Each file in this list is an input to a reader thread.
- `writer_file`: A file that contains a list of file names. Each file in this list is an input to a writer thread.
- `items_file`: The actual data file for your program. Each line of the file is either blank or contains some value.


## Unit tests

To run the unit tests, simply be in `build` directory and execute:

```
cd test
./cache_main_test
./reader_test
./writer_test
./cache_manager_test
```

This will run a series of tests to validate the functionality and correctness of the Cache-Manager program.


Sure, here's an updated PRD with additional information:


# User Needs

We want to be able to run the program from the command line with the following arguments:

- The size of the cache (an integer value)
- A file containing a list of reader file names (one per line)
- A file containing a list of writer file names (one per line)
- The name of the data file containing the items

Program should spawn multiple reader and writer threads as specified in the input files, and perform caching of frequently accessed items. 


# Assumptions

1. The input files (reader, writer, and items) are well-formed and have valid contents.
2. The cache size, number of readers, and number of writers are reasonable and within the limits of available system resources.
3. The program will not encounter any I/O errors while reading from or writing to the files.


# Solution Overview

The program consists of the following components:

- Cache: A data structure that stores frequently accessed items in memory. The cache has a fixed capacity and uses a least recently used (LRU) eviction policy to remove items when the cache is full.
- Cache Manager: A class that coordinates access to the cache and item manager. A class that handles read and write operations to the original data source (the data file). The cache manager reads items from the cache if they are present, and from the item manager otherwise. The cache manager also writes items to the cache and the item manager.
- Reader: A class that represents a reader thread. The reader reads items from the cache or data source and writes them to an output file.
- Writer: A class that represents a writer thread. The writer writes items to the original data source.
- Main Function: The main function initializes the cache, starts the reader and writer threads, and waits for them to finish.


# Technical Requirements

The program must meet the following technical requirements:

- The program must be written in C++ using object-oriented programming principles.
- The program must use classes and encapsulation to separate concerns and improve modularity.
- The program must use a file-based input/output format, with files containing lists of reader and writer file names.
- The program must use a least recently used (LRU) eviction policy to remove items from the cache when it is full.
- The program must handle dirty cache items, where a writer is modifying an item that is already cached.
- The program must handle all corner cases and failures gracefully, and provide meaningful error messages to the user.
- The program must include unit tests to test all components of the program, including the cache, item manager, cache manager, reader, and writer classes.
- The program must handle concurrency correctly and efficiently, using synchronization primitives like locks or mutexes as necessary.

# Design considerations

Currently, the program specifically prioritize read-heavyworkloads. The implementation is quite simple (LRU) and does not include advanced cache eviction policies, write buffering, or caching policies like write-through, or write-back.

In its current state, the program reads data from an input file, stores it in a buffer, writes the buffer's content to another file, and searches for specific items within the buffer. Its performance will depend on the balance of read and write operations in the input files provided (i.e., reader_file and writer_file).

When our program is read-heavy, the cache should prioritize keeping frequently accessed items in the cache to minimize the time spent reading from the disk. This can be achieved by implementing a Least Recently Used (LRU) or Most Frequently Used (MFU) cache replacement policy.

## Future Work
When program is write-heavy, we may want to focus on minimizing the time spent on writing to the disk. This can be achieved by implementing a write buffer that batches multiple write operations before flushing them to the disk. Additionally, we can use a write-through or write-back caching policy to control when and how the cache updates the disk.

