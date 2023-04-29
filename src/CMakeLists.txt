add_library(cache_main cache_main.cc reader.cc writer.cc cache_manager.cc)

target_include_directories(cache_main PUBLIC include/)

# Define sources
set(SOURCES
    cache_main.cc
    cache_manager.cc
    main.cc
    reader.cc
    writer.cc
)

# Automatically include all files in the 'data' folder
file(GLOB DATA_FILES "data/*")

# Copy each file in the list to the build directory
foreach(data_file ${DATA_FILES})
  get_filename_component(file_name ${data_file} NAME)
  configure_file(${data_file} ${CMAKE_CURRENT_BINARY_DIR}/${file_name} COPYONLY)
endforeach()

# Define headers
set(HEADERS
    include/cache_main.h
    include/cache_manager.h
    include/reader.h
    include/writer.h
)

# Create library
add_library(cache_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(cache_lib PUBLIC include/)

add_executable(cache_handler main.cc)
target_link_libraries(cache_handler PRIVATE cache_lib)
