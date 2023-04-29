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

After building the project, you can run the program with the following command:

```
./cache <size_of_cache> <reader_file> <writer_file> <items_file>
```

- `size_of_cache`: An integer value indicating the number of elements that the cache can hold at any given time.
- `reader_file`: A file that contains a list of file names. Each file in this list is an input to a reader thread.
- `writer_file`: A file that contains a list of file names. Each file in this list is an input to a writer thread.
- `items_file`: The actual data file for your program. Each line of the file is either blank or contains one number.

## Design considerations

When your program is read-heavy, the cache should prioritize keeping frequently accessed items in the cache to minimize the time spent reading from the disk. This can be achieved by implementing a Least Recently Used (LRU) or Most Frequently Used (MFU) cache replacement policy.

On the other hand, when your program is write-heavy, you may want to focus on minimizing the time spent on writing to the disk. This can be achieved by implementing a write buffer that batches multiple write operations before flushing them to the disk. Additionally, you can use a write-through or write-back caching policy to control when and how the cache updates the disk.

## Assumptions

1. The input files (reader, writer, and items) are well-formed and have valid contents.
2. The cache size, number of readers, and number of writers are reasonable and within the limits of available system resources.
3. The program will not encounter any I/O errors while reading from or writing to the files.

## Unit tests

To run the unit tests, simply execute:

```
./cache_test
```

This will run a series of tests to validate the functionality and correctness of the Cache-Manager program.
