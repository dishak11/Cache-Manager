cmake_minimum_required(VERSION 3.16)
project(CacheTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(cache_handler)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)