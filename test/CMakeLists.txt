include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(cache_main_test cache_main_test.cc)
add_executable(reader_test reader_test.cc)
add_executable(writer_test writer_test.cc)
add_executable(cache_manager_test cache_manager_test.cc)

target_link_libraries(cache_main_test
 PUBLIC
  GTest::GTest
  cache_main)

target_link_libraries(reader_test
  PUBLIC
   GTest::GTest
   cache_main)

target_link_libraries(writer_test
   PUBLIC
    GTest::GTest
    cache_main)

target_link_libraries(cache_manager_test
    PUBLIC
     GTest::GTest
     cache_main)
add_test(cache_main_gtest cache_main_test)
add_test(reader_gtest reader_test)
add_test(writer_gtest writer_test)
add_test(cache_manager_gtest cache_manager_test)