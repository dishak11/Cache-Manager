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

## Design considerations

Currently, the program does not specifically prioritize read-heavy or write-heavy workloads. The implementation is quite simple (MFU) and does not include advanced cache eviction policies, write buffering, or caching policies like write-through, or write-back.

In its current state, the program reads data from an input file, stores it in a buffer, writes the buffer's content to another file, and searches for specific items within the buffer. The program does not have a dedicated mechanism to handle read-heavy or write-heavy workloads, and its performance will depend on the balance of read and write operations in the input files provided (i.e., reader_file and writer_file).

When our program is read-heavy, the cache should prioritize keeping frequently accessed items in the cache to minimize the time spent reading from the disk. This can be achieved by implementing a Least Recently Used (LRU) or Most Frequently Used (MFU) cache replacement policy.

Future Work: 
When your program is write-heavy, you may want to focus on minimizing the time spent on writing to the disk. This can be achieved by implementing a write buffer that batches multiple write operations before flushing them to the disk. Additionally, we can use a write-through or write-back caching policy to control when and how the cache updates the disk.

## Assumptions

1. The input files (reader, writer, and items) are well-formed and have valid contents.
2. The cache size, number of readers, and number of writers are reasonable and within the limits of available system resources.
3. The program will not encounter any I/O errors while reading from or writing to the files.

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
